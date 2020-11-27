#include <resea/printf.h>
#include <string.h>

// Flutter expects libc is glibc, we need a workaround on stdin/stdout/stderr...
struct __FILE;
struct _reent {
  int _errno;
  struct __FILE *_stdin, *_stdout, *_stderr;

  // Assuming the following fields in newlib do not affect alignments above...
};

extern struct _reent *_impure_ptr;
#define _REENT (_impure_ptr)
struct __FILE *stdin = NULL;
struct __FILE *stdout = NULL;
struct __FILE *stderr = NULL;

void init_shims(void) {
    stdin = _REENT->_stdin;
    stdout = _REENT->_stdout;
    stderr = _REENT->_stderr;
}

int accept() {
    TRACE("shim: %s", __func__);
    return 0;
}

int access() {
    TRACE("shim: %s", __func__);
    return 0;
}

int bind() {
    TRACE("shim: %s", __func__);
    return 0;
}

int catclose() {
    TRACE("shim: %s", __func__);
    return 0;
}

int catgets() {
    TRACE("shim: %s", __func__);
    return 0;
}

int catopen() {
    TRACE("shim: %s", __func__);
    return 0;
}

int chdir() {
    TRACE("shim: %s", __func__);
    return 0;
}

int clock_gettime() {
    TRACE("shim: %s", __func__);
    return 0;
}

int close() {
    TRACE("shim: %s", __func__);
    return 0;
}

int closedir() {
    TRACE("shim: %s", __func__);
    return 0;
}

int connect() {
    TRACE("shim: %s", __func__);
    return 0;
}

int __ctype_b_loc() {
    TRACE("shim: %s", __func__);
    return 0;
}

int __ctype_get_mb_cur_max() {
    TRACE("shim: %s", __func__);
    return 1;
}

int __ctype_tolower_loc() {
    TRACE("shim: %s", __func__);
    return 0;
}

int dladdr() {
    TRACE("shim: %s", __func__);
    return 0;
}

int dlclose() {
    TRACE("shim: %s", __func__);
    return 0;
}

int dlerror() {
    TRACE("shim: %s", __func__);
    return 0;
}

int dlopen() {
    TRACE("shim: %s", __func__);
    return 0;
}

int dlsym() {
    TRACE("shim: %s", __func__);
    return 0;
}

int dup() {
    TRACE("shim: %s", __func__);
    return 0;
}

int dup2() {
    TRACE("shim: %s", __func__);
    return 0;
}

int epoll_create() {
    TRACE("shim: %s", __func__);
    return 0;
}

int epoll_ctl() {
    TRACE("shim: %s", __func__);
    return 0;
}

int epoll_wait() {
    TRACE("shim: %s", __func__);
    return 0;
}

int __errno_location() {
    TRACE("shim: %s", __func__);
    return 0;
}

int execvp() {
    TRACE("shim: %s", __func__);
    return 0;
}

int _exit() {
    TRACE("shim: %s", __func__);
    return 0;
}

int faccessat() {
    TRACE("shim: %s", __func__);
    return 0;
}

int fcntl() {
    TRACE("shim: %s", __func__);
    return 0;
}

int fdopendir() {
    TRACE("shim: %s", __func__);
    return 0;
}

int fopen64() {
    TRACE("shim: %s", __func__);
    return 0;
}

int fork() {
    TRACE("shim: %s", __func__);
    return 0;
}

int freeaddrinfo() {
    TRACE("shim: %s", __func__);
    return 0;
}

int freeifaddrs() {
    TRACE("shim: %s", __func__);
    return 0;
}

int fseeko64() {
    TRACE("shim: %s", __func__);
    return 0;
}

int fstat() {
    TRACE("shim: %s", __func__);
    return 0;
}

int fsync() {
    TRACE("shim: %s", __func__);
    return 0;
}

int ftello64() {
    TRACE("shim: %s", __func__);
    return 0;
}

int ftruncate64() {
    TRACE("shim: %s", __func__);
    return 0;
}

int __fxstat64() {
    TRACE("shim: %s", __func__);
    return 0;
}

int __fxstatat64() {
    TRACE("shim: %s", __func__);
    return 0;
}

int gai_strerror() {
    TRACE("shim: %s", __func__);
    return 0;
}

int getaddrinfo() {
    TRACE("shim: %s", __func__);
    return 0;
}

int getauxval() {
    TRACE("shim: %s", __func__);
    return 0;
}

int getcwd() {
    TRACE("shim: %s", __func__);
    return 0;
}

int gethostname() {
    TRACE("shim: %s", __func__);
    return 0;
}

int getifaddrs() {
    TRACE("shim: %s", __func__);
    return 0;
}

int getnameinfo() {
    TRACE("shim: %s", __func__);
    return 0;
}

int getpagesize() {
    TRACE("shim: %s", __func__);
    return 0;
}

int getpeername() {
    TRACE("shim: %s", __func__);
    return 0;
}

int getpid() {
    TRACE("shim: %s", __func__);
    return 0;
}

int getrusage() {
    TRACE("shim: %s", __func__);
    return 0;
}

int getsockname() {
    TRACE("shim: %s", __func__);
    return 0;
}

int getsockopt() {
    TRACE("shim: %s", __func__);
    return 0;
}

int gettimeofday() {
    TRACE("shim: %s", __func__);
    return 0;
}

int if_nametoindex() {
    TRACE("shim: %s", __func__);
    return 0;
}

int inet_ntop() {
    TRACE("shim: %s", __func__);
    return 0;
}

int inet_pton() {
    TRACE("shim: %s", __func__);
    return 0;
}

int inotify_add_watch() {
    TRACE("shim: %s", __func__);
    return 0;
}

int inotify_init1() {
    TRACE("shim: %s", __func__);
    return 0;
}

int inotify_rm_watch() {
    TRACE("shim: %s", __func__);
    return 0;
}

int ioctl() {
    TRACE("shim: %s", __func__);
    return 0;
}

int isatty() {
    TRACE("shim: %s", __func__);
    return 0;
}

int __isinf() {
    TRACE("shim: %s", __func__);
    return 0;
}

int __isnan() {
    TRACE("shim: %s", __func__);
    return 0;
}

int __isoc99_fscanf() {
    TRACE("shim: %s", __func__);
    return 0;
}

int __isoc99_sscanf() {
    TRACE("shim: %s", __func__);
    return 0;
}

int __isoc99_vsscanf() {
    TRACE("shim: %s", __func__);
    return 0;
}

int kill() {
    TRACE("shim: %s", __func__);
    return 0;
}

int listen() {
    TRACE("shim: %s", __func__);
    return 0;
}

int lseek() {
    TRACE("shim: %s", __func__);
    return 0;
}

int lseek64() {
    TRACE("shim: %s", __func__);
    return 0;
}

int __lxstat64() {
    TRACE("shim: %s", __func__);
    return 0;
}

int mkdir() {
    TRACE("shim: %s", __func__);
    return 0;
}

int mkdirat() {
    TRACE("shim: %s", __func__);
    return 0;
}

int mmap64() {
    TRACE("shim: %s", __func__);
    return 0;
}

int mprotect() {
    TRACE("shim: %s", __func__);
    return 0;
}

int munmap() {
    TRACE("shim: %s", __func__);
    return 0;
}

int nanosleep() {
    TRACE("shim: %s", __func__);
    return 0;
}

int open() {
    TRACE("shim: %s", __func__);
    return 0;
}

int open64() {
    TRACE("shim: %s", __func__);
    return 0;
}

int openat64() {
    TRACE("shim: %s", __func__);
    return 0;
}

int opendir() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pipe() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pipe2() {
    TRACE("shim: %s", __func__);
    return 0;
}

int poll() {
    TRACE("shim: %s", __func__);
    return 0;
}

int posix_memalign() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pread64() {
    TRACE("shim: %s", __func__);
    return 0;
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

int pthread_cond_wait() {
    TRACE("shim: %s", __func__);
    return 0;
}

int pthread_create() {
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

int read() {
    TRACE("shim: %s", __func__);
    return 0;
}

int readdir64() {
    TRACE("shim: %s", __func__);
    return 0;
}

int readlink() {
    TRACE("shim: %s", __func__);
    return 0;
}

int readlinkat() {
    TRACE("shim: %s", __func__);
    return 0;
}

int realpath() {
    TRACE("shim: %s", __func__);
    return 0;
}

int recvfrom() {
    TRACE("shim: %s", __func__);
    return 0;
}

int renameat() {
    TRACE("shim: %s", __func__);
    return 0;
}

int rewinddir() {
    TRACE("shim: %s", __func__);
    return 0;
}

int sbrk() {
    TRACE("shim: %s", __func__);
    return 0;
}

int sched_yield() {
    TRACE("shim: %s", __func__);
    return 0;
}

int sem_destroy() {
    TRACE("shim: %s", __func__);
    return 0;
}

int sem_init() {
    TRACE("shim: %s", __func__);
    return 0;
}

int sem_post() {
    TRACE("shim: %s", __func__);
    return 0;
}

int sem_trywait() {
    TRACE("shim: %s", __func__);
    return 0;
}

int sem_wait() {
    TRACE("shim: %s", __func__);
    return 0;
}

int sendfile64() {
    TRACE("shim: %s", __func__);
    return 0;
}

int sendto() {
    TRACE("shim: %s", __func__);
    return 0;
}

int _setjmp() {
    TRACE("shim: %s", __func__);
    return 0;
}

int setpriority() {
    TRACE("shim: %s", __func__);
    return 0;
}

int setrlimit64() {
    TRACE("shim: %s", __func__);
    return 0;
}

int setsid() {
    TRACE("shim: %s", __func__);
    return 0;
}

int setsockopt() {
    TRACE("shim: %s", __func__);
    return 0;
}

int shutdown() {
    TRACE("shim: %s", __func__);
    return 0;
}

int sigaction() {
    TRACE("shim: %s", __func__);
    return 0;
}

int sigaddset() {
    TRACE("shim: %s", __func__);
    return 0;
}

int sigemptyset() {
    TRACE("shim: %s", __func__);
    return 0;
}

int sigprocmask() {
    TRACE("shim: %s", __func__);
    return 0;
}

int socket() {
    TRACE("shim: %s", __func__);
    return 0;
}

int stat() {
    TRACE("shim: %s", __func__);
    return 0;
}

int symlinkat() {
    TRACE("shim: %s", __func__);
    return 0;
}

long syscall(long n) {
    INFO("syscall n = %d", n);
    if (n == 186) {
        // gettid
        return 1;
    }

    return 0;
}

int sysconf() {
    TRACE("shim: %s", __func__);
    return 0;
}

int tcgetattr() {
    TRACE("shim: %s", __func__);
    return 0;
}

int tcsetattr() {
    TRACE("shim: %s", __func__);
    return 0;
}

int timerfd_create() {
    TRACE("shim: %s", __func__);
    return 0;
}

int timerfd_settime() {
    TRACE("shim: %s", __func__);
    return 0;
}

int __timezone() {
    TRACE("shim: %s", __func__);
    return 0;
}

int timezone() {
    TRACE("shim: %s", __func__);
    return 0;
}

int tzname() {
    TRACE("shim: %s", __func__);
    return 0;
}

int __umodti3() {
    TRACE("shim: %s", __func__);
    return 0;
}

int uname() {
    TRACE("shim: %s", __func__);
    return 0;
}

int unlink() {
    TRACE("shim: %s", __func__);
    return 0;
}

int unlinkat() {
    TRACE("shim: %s", __func__);
    return 0;
}

int utimensat() {
    TRACE("shim: %s", __func__);
    return 0;
}

int wait() {
    TRACE("shim: %s", __func__);
    return 0;
}

long write(int fd, const void *buf, size_t len) {
    TRACE("shim: %s(fd=%d, buf=%p, len=%d)", __func__, fd, buf, len);
    if (fd == 1 || fd == 2) {
        if (strlen(buf) > len) {
            WARN_DBG("not a string?");
            return len;
        }

        DBG("%s: %s", fd == 1 ? "stdout" : "stderr", buf);
    }

    return len;
}

int __xstat64() {
    TRACE("shim: %s", __func__);
    return 0;
}

int __dso_handle() {
    TRACE("shim: %s", __func__);
    return 0;
}
