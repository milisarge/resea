#include <resea/printf.h>
#include <resea/ipc.h>
#include <resea/task.h>
#include <resea/malloc.h>
#include <string.h>
#include "libc_shims.h"

struct __packed thread_info {
    vaddr_t ip;
    vaddr_t sp;
    vaddr_t arg;
    vaddr_t tls;
    task_t task;
};

#define PTHREAD_KEY_MAX 16
static int next_tls_key = 0;
struct tls_data {
    const void *value;
};

struct tls {
    struct tls_data keys[PTHREAD_KEY_MAX];
    void *heap;
    size_t heap_size;
};

extern struct thread_info __thread_info;

static struct tls *current_tls(void) {
    return (struct tls *) __thread_info.tls;
}

// In asm.S.
void pthread_thread_entry(void);

void malloc_init_with(void *heap, size_t heap_size);
void pthread_before_start_routine(void) {
    // struct tls *tls = current_tls();

    // // Yse the thread-local heap area so that we don't need to add locks in the
    // // standard library.
    // malloc_init_with(tls->heap, tls->heap_size);
}

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start)(void *), void *arg) {
    TRACE("[%d] shim: %s", task_self(), __func__);
    size_t stack_size = 16 * 1024;

    struct tls *tls = malloc(sizeof(*tls));
    memset(tls, 0, sizeof(*tls));
    tls->heap_size = 32 * 1024;
    tls->heap = malloc(tls->heap_size);

    struct message m;
    m.type = TASK_SPAWN_THREAD_MSG;
    m.task_spawn_thread.roommate = task_self();
    m.task_spawn_thread.entry = (vaddr_t) pthread_thread_entry;
    m.task_spawn_thread.ip = (vaddr_t) start;
    m.task_spawn_thread.sp = (vaddr_t) malloc(stack_size) + stack_size;
    m.task_spawn_thread.arg = (vaddr_t) arg;
    m.task_spawn_thread.tls = (vaddr_t) tls;
    ASSERT_OK(ipc_call(INIT_TASK, &m));
    *thread = m.task_spawn_thread_reply.task;
    return 0;
}

pthread_t pthread_self(void) {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return task_self();
}

int pthread_key_create(pthread_key_t *key, void (*destructor)(void*)) {
    TRACE("[%d] shim: %s", task_self(), __func__);
    ASSERT(next_tls_key < PTHREAD_KEY_MAX);
    *key = next_tls_key++;
    return 0;
}

int pthread_setspecific(pthread_key_t key, const void *value) {
    TRACE("[%d] shim: %s", task_self(), __func__);
    ASSERT(key < PTHREAD_KEY_MAX);
    struct tls_data *data = &current_tls()->keys[key];
    data->value = value;
    return 0;
}

void *pthread_getspecific(pthread_key_t key) {
    TRACE("[%d] shim: %s", task_self(), __func__);
    ASSERT(key < PTHREAD_KEY_MAX);
    struct tls_data *data = &current_tls()->keys[key];
    return (void *) data->value;
}

void init_pthread_shims(void) {
    struct tls *tls = malloc(sizeof(*tls));
    memset(tls, 0, sizeof(*tls));
    __thread_info.tls = (vaddr_t) tls;
}

int pthread_mutex_destroy(pthread_mutex_t *mutex) {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr) {
    TRACE("[%d] shim: %s", task_self(), __func__);
    *mutex = PTHREAD_MUTEX_INITIALIZER;
    return 0;
}

int pthread_mutex_lock(pthread_mutex_t *mutex) {
    // TRACE("[%d] shim: %s", task_self(), __func__);
    while (!__sync_bool_compare_and_swap(mutex, PTHREAD_MUTEX_UNLOCKED, PTHREAD_MUTEX_LOCKED)) {
        __asm__ __volatile__("pause");
    }
    return 0;
}

int pthread_mutex_trylock(pthread_mutex_t *mutex) {
    TRACE("[%d] shim: %s", task_self(), __func__);
    if (__sync_bool_compare_and_swap(mutex, PTHREAD_MUTEX_UNLOCKED, PTHREAD_MUTEX_LOCKED)) {
        return 0;
    } else {
        return -1;
    }
}

int pthread_mutex_unlock(pthread_mutex_t *mutex) {
    // TRACE("[%d] shim: %s", task_self(), __func__);
    __sync_bool_compare_and_swap(mutex, PTHREAD_MUTEX_LOCKED, PTHREAD_MUTEX_UNLOCKED);
    return 0;
}

int pthread_cond_init() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_cond_signal() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    for (task_t task = 0; task < CONFIG_NUM_TASKS; task++) {
        ipc_notify(task, NOTIFY_WAKE);
    }
    return 0;
}

int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex) {
    TRACE("[%d] shim: %s", task_self(), __func__);
    pthread_mutex_unlock(mutex);
    struct message m;
    ipc_recv(IPC_ANY, &m);
    return 0;
}

static uint8_t *brk_crnt = NULL, *brk_end = NULL;

void *do_malloc(size_t size);
void do_free(void *ptr);
pthread_mutex_t malloc_lock = PTHREAD_MUTEX_INITIALIZER;

void *malloc(size_t size) {
    pthread_mutex_lock(&malloc_lock);
    void *ptr = do_malloc(size);
    pthread_mutex_unlock(&malloc_lock);
    return ptr;
}

void free(void *ptr) {
    pthread_mutex_lock(&malloc_lock);
    do_free(ptr);
    pthread_mutex_unlock(&malloc_lock);
}

void *sbrk(long long increment) {
    TRACE("[%d] shim: %s(%d)", task_self(), __func__, increment);
    if (!brk_crnt) {
        size_t new_chunk_len = 32 * 1024 * 1024;
        struct message m;
        m.type = VM_ALLOC_PAGES_MSG;
        m.vm_alloc_pages.num_pages = new_chunk_len / PAGE_SIZE;
        m.vm_alloc_pages.paddr = 0;
        ASSERT_OK(ipc_call(INIT_TASK, &m));
        ASSERT(m.type == VM_ALLOC_PAGES_REPLY_MSG);
        brk_crnt = (uint8_t *) m.vm_alloc_pages_reply.vaddr;
        brk_end = brk_crnt + new_chunk_len;
    }

    if ((vaddr_t) brk_crnt + increment >= (vaddr_t) brk_end) {
        PANIC("out of brk");
    }

    brk_crnt += increment;
    return brk_crnt;
}
// --------------------------------------------------------------------

int pthread_attr_destroy() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_attr_getstack() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_attr_init() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_attr_setdetachstate() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_attr_setstacksize() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_condattr_destroy() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_condattr_init() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_condattr_setclock() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_cond_broadcast() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_cond_destroy() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_cond_timedwait() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_detach() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_getattr_np() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_join() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_key_delete() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_mutexattr_destroy() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_mutexattr_init() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_mutexattr_settype() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_once() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_rwlock_destroy() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_rwlock_init() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_rwlock_rdlock() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_rwlock_unlock() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_rwlock_wrlock() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_setname_np() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pthread_sigmask() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}
