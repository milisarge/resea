#include <resea/printf.h>
#include <resea/ipc.h>
#include <resea/task.h>
#include <resea/malloc.h>
#include <string.h>
#include "libc_shims.h"

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

int pthread_cond_wait() {
    TRACE("shim: %s", __func__);
    PANIC("");
    return 0;
}

int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                   void *(*start)(void *), void *arg) {
    TRACE("shim: %s", __func__);
    size_t stack_size = 16 * 1024;
    struct message m;
    m.type = TASK_SPAWN_THREAD_MSG;
    m.task_spawn_thread.roommate = task_self();
    m.task_spawn_thread.entry = (vaddr_t) start;
    m.task_spawn_thread.arg = (vaddr_t) arg;
    m.task_spawn_thread.sp = (vaddr_t) malloc(stack_size) + stack_size;
    ASSERT_OK(ipc_call(INIT_TASK, &m));
    *thread = m.task_spawn_thread_reply.task;
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

int pthread_getspecific() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_join() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_key_create() {
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

int pthread_self() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_setname_np() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_setspecific() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_sigmask() {
    TRACE("shim: %s", __func__);
    return 0;
}
