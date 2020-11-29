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
struct tls_data {
    bool in_use;
    const void *value;
};

struct tls {
    struct tls_data keys[PTHREAD_KEY_MAX];
};

extern struct thread_info __thread_info;

static struct tls *current_tls(void) {
    return (struct tls *) __thread_info.tls;
}

int pthread_cond_wait() {
    TRACE("shim: %s", __func__);
    struct message m;
    ipc_recv(IPC_ANY, &m);
    return 0;
}

void pthread_thread_entry(void);

void pthread_before_start_routine(void) {

}

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start)(void *), void *arg) {
    TRACE("shim: %s", __func__);
    size_t stack_size = 16 * 1024;

    struct tls *tls = malloc(sizeof(*tls));
    memset(tls, 0, sizeof(*tls));

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
    TRACE("shim: %s", __func__);
    return task_self();
}

int pthread_key_create(pthread_key_t *key, void (*destructor)(void*)) {
    TRACE("shim: %s", __func__);
    for (int i = 0; i < PTHREAD_KEY_MAX; i++) {
        struct tls_data *data = &current_tls()->keys[i];
        if (data->in_use) {
            data->in_use = true;
            *key = i;
            return 0;
        }
    }

    PANIC("too many tls data");
}

int pthread_setspecific(pthread_key_t key, const void *value) {
    TRACE("shim: %s", __func__);
    ASSERT(key < PTHREAD_KEY_MAX);
    struct tls_data *data = &current_tls()->keys[key];
    ASSERT(data->in_use);
    data->value = value;
    return 0;
}

void *pthread_getspecific(pthread_key_t key) {
    TRACE("shim: %s", __func__);
    ASSERT(key < PTHREAD_KEY_MAX);
    struct tls_data *data = &current_tls()->keys[key];
    ASSERT(data->in_use);
    return (void *) data->value;
}

int pthread_attr_destroy() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_attr_getstack() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_attr_init() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_attr_setdetachstate() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_attr_setstacksize() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_condattr_destroy() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_condattr_init() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_condattr_setclock() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_cond_broadcast() {
    TRACE("%s", __func__);
    return 0;
}

int pthread_cond_destroy() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_cond_init() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_cond_signal() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_cond_timedwait() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_detach() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_getattr_np() {
    TRACE("shim: %s", __func__);
    return 0;
}


int pthread_join() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_key_delete() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_mutexattr_destroy() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_mutexattr_init() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_mutexattr_settype() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_mutex_destroy() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_mutex_init() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_mutex_lock() {
    TRACE("pthread_mutex_lock");
    return 0;
}

int pthread_mutex_trylock() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_mutex_unlock() {
    TRACE("pthread_mutex_unlock");
    return 0;
}

int pthread_once() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_rwlock_destroy() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_rwlock_init() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_rwlock_rdlock() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_rwlock_unlock() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_rwlock_wrlock() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_setname_np() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_sigmask() {
    TRACE("shim: %s", __func__);
    return 0;
}
