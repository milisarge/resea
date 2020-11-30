#include <resea/task.h>
#include <resea/printf.h>

int accept() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int access() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int bind() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int catclose() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int catgets() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int catopen() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int chdir() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int clock_gettime() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int close() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int closedir() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int connect() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int __ctype_b_loc() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int __ctype_get_mb_cur_max() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 1;
}

int __ctype_tolower_loc() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int dladdr() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int dlclose() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int dlerror() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int dlopen() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int dlsym() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int dup() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int dup2() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int epoll_create() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int epoll_ctl() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int __errno_location() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int execvp() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int _exit() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int faccessat() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int fcntl() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int fdopendir() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int fopen64() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int fork() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int freeaddrinfo() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int freeifaddrs() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int fseeko64() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int fstat() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int fsync() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int ftello64() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int ftruncate64() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int __fxstatat64() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int gai_strerror() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int getaddrinfo() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int getauxval() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int getcwd() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int gethostname() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int getifaddrs() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int getnameinfo() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int getpagesize() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int getpeername() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int getpid() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int getrusage() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int getsockname() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int getsockopt() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int gettimeofday() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int if_nametoindex() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int inet_ntop() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int inet_pton() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int inotify_add_watch() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int inotify_init1() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int inotify_rm_watch() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int ioctl() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int isatty() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int __isinf() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int __isnan() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int __isoc99_fscanf() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int __isoc99_sscanf() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int __isoc99_vsscanf() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int kill() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int listen() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int lseek() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int lseek64() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int __lxstat64() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int mkdir() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int mkdirat() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int mprotect() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int munmap() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int nanosleep() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int open() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int open64() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int opendir() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pipe() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pipe2() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int poll() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int posix_memalign() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int pread64() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int read() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int readdir64() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int readlinkat() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int realpath() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int recvfrom() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int renameat() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int rewinddir() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int sched_yield() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int sem_destroy() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int sem_init() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int sem_post() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int sem_trywait() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int sem_wait() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int sendfile64() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int sendto() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int _setjmp() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int setpriority() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int setrlimit64() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int setsid() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int setsockopt() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int shutdown() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int sigaction() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int sigaddset() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int sigemptyset() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int sigprocmask() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int socket() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int stat() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int symlinkat() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int sysconf() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int tcgetattr() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int tcsetattr() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int timerfd_create() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int timerfd_settime() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int __timezone() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int timezone() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int tzname() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int __umodti3() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int uname() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int unlink() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int unlinkat() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int utimensat() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int wait() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int __xstat64() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}

int __dso_handle() {
    TRACE("[%d] shim: %s", task_self(), __func__);
    return 0;
}
