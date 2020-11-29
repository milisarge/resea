#include <resea/printf.h>

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

int execvp() {
    TRACE("shim: %s", __func__);
    return 0;
}

int _exit() {
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

int dup() {
    TRACE("shim: %s", __func__);
    return 0;
}

int dup2() {
    TRACE("shim: %s", __func__);
    return 0;
}

int __errno_location() {
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
