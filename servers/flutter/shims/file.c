#include <resea/printf.h>
#include <resea/ipc.h>
#include <resea/task.h>
#include <resea/malloc.h>
#include <string.h>
#include "libc_shims.h"

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

void printchar(char ch);
long write(int fd, const void *buf, size_t len) {
    if (fd == 1 || fd == 2) {
        printchar('\e');
        printchar('[');
        printchar('1');
        printchar(';');
        printchar('9');
        printchar('5');
        printchar('m');
        for (size_t i = 0; i < len; i++) {
            printchar(*((char *) buf + i));
        }
        printchar('\e');
        printchar('[');
        printchar('0');
        printchar('m');
    } else {
        WARN_DBG("shim: %s(fd=%d, buf=%p, len=%d)", __func__, fd, buf, len);
    }

    return len;
}

#define FD_BASE 10
#define FD_MAX 128
struct opened_file {
    bool in_use;
    int fd;
    char *path;
};

struct opened_file opened_files[FD_MAX];

struct opened_file *alloc_fd(const char *path) {
    for (int i = 0; i < FD_MAX; i++) {
        if (!opened_files[i].in_use) {
            opened_files[i].in_use = true;
            opened_files[i].fd = i + FD_BASE;
            opened_files[i].path = strdup(path);
            return &opened_files[i];
        }
    }

    PANIC("too many opened files");
}

struct opened_file *lookup_fd(int fd) {
    ASSERT(fd >= FD_BASE);
    ASSERT(fd < FD_BASE + FD_MAX);
    struct opened_file *f = &opened_files[fd - FD_BASE];
    ASSERT(f->fd == fd);
    return f;
}

# define AT_FDCWD -100
int openat64(int dirfd, const char *path, int mode) {
    TRACE("[%d] shim: %s(dirfd=%d, path=\"%s\")", task_self(), __func__, dirfd, path);
    ASSERT(dirfd == AT_FDCWD);
    struct opened_file *f = alloc_fd(path);
    return f->fd;
}

int readlink(const char *path, char *buf, size_t bufsiz) {
    TRACE("[%d] shim: %s(path=%s)", task_self(), __func__, path);
    strncpy(buf, path, bufsiz);
    return strlen(buf);
}

struct stat64 {
    unsigned long st_dev;
    unsigned long st_ino;
    unsigned long st_nlink;
    unsigned st_mode;
    unsigned st_uid;
    unsigned st_gid;
    unsigned __pad0;
    unsigned long st_rdev;
    long st_size;
    // TODO: Add remaining fields.
} __packed;

#define S_IFREG   0100000
#define S_IFDIR   0040000

bool endswith(const char *s, const char *suffix) {
    size_t s_len = strlen(s);
    size_t suffix_len = strlen(suffix);
    return s_len >= suffix_len && !strcmp(&s[s_len - suffix_len], suffix);
}

int __fxstat64(int vers, int fd, struct stat64 *buf) {
    OOPS("[%d] shim: %s(fd=%d)", task_self(), __func__, fd);
    struct opened_file *f = lookup_fd(fd);

    memset(buf, 0, sizeof(*buf));
    buf->st_mode = endswith(f->path, "/") ? S_IFDIR : S_IFREG;
    buf->st_size = 0;
    return 0;
}

int epoll_wait(void) {
    DBG("[%d] shim: %s", task_self(), __func__);
    while (true) {
        struct message m;
        ipc_recv(IPC_ANY, &m);
    }
    return 0;
}

void init_file_shims(void) {
    stdin = _REENT->_stdin;
    stdout = _REENT->_stdout;
    stderr = _REENT->_stderr;
}
