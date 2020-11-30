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

struct embedded_file {
    const char *path;
    unsigned mode;
    uint8_t *data;
    uint8_t *data_end;
    size_t size;
};

#define FD_BASE 10
#define FD_MAX 128
struct opened_file {
    bool in_use;
    int fd;
    char *path;
    struct embedded_file *embedded;
};


struct opened_file opened_files[FD_MAX];

extern char __icu_data[];
extern char __icu_data_end[];
struct embedded_file embedded_files[] = {
    {
        .path = "/assets/",
        .mode = S_IFDIR,
        .data = NULL,
        .data_end = NULL,
        .size = 0
    },
    {
        .path = "/icu_data/icudtl.dat",
        .mode = S_IFREG,
        .data = (uint8_t *) __icu_data,
        .data_end = (uint8_t *) __icu_data_end,
        .size = 0,
    },
    {
        .path = NULL,
        .mode = S_IFREG,
        .data = NULL,
        .data_end = NULL,
        .size = 0
    },
};

struct embedded_file *lookup_embedded_file(const char *path) {
    int i = 0;
    while (embedded_files[i].path) {
        struct embedded_file *f = &embedded_files[i];
        if (f->data_end) {
            f->size = (size_t) f->data_end - (size_t) f->data;
        }

        if (!resea_strcmp(f->path, path)) {
            return f;
        }

        i++;
    }

    WARN_DBG("unknown file: %s", path);
    return NULL;
}

struct opened_file *alloc_fd(const char *path) {
    for (int i = 0; i < FD_MAX; i++) {
        if (!opened_files[i].in_use) {
            opened_files[i].in_use = true;
            opened_files[i].fd = i + FD_BASE;
            opened_files[i].path = strdup(path);
            opened_files[i].embedded = lookup_embedded_file(path);
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

int openat64(int dirfd, const char *path, int mode) {
    TRACE("[%d] shim: %s(dirfd=%d, path=\"%s\")", task_self(), __func__, dirfd, path);
    ASSERT(dirfd == AT_FDCWD);
    struct opened_file *f = alloc_fd(path);
    return f->fd;
}

int readlink(const char *path, char *buf, size_t bufsiz) {
    TRACE("[%d] shim: %s(path=%s)", task_self(), __func__, path);
    resea_strncpy(buf, path, bufsiz);
    return strlen(buf);
}

bool endswith(const char *s, const char *suffix) {
    size_t s_len = strlen(s);
    size_t suffix_len = strlen(suffix);
    return s_len >= suffix_len && !resea_strcmp(&s[s_len - suffix_len], suffix);
}

int __fxstat64(int vers, int fd, struct stat64 *buf) {
    OOPS("[%d] shim: %s(fd=%d)", task_self(), __func__, fd);
    struct opened_file *f = lookup_fd(fd);

    memset(buf, 0, sizeof(*buf));
    buf->st_mode = f->embedded->mode;
    buf->st_size = f->embedded->size;
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


void *mmap64(void *addr, size_t length, int prot, int flags, int fd, long offset) {
    TRACE("[%d] shim: %s(fd=%d, off=%d)", task_self(), __func__, fd, offset);
    if (fd == -1) {
        struct message m;
        m.type = VM_ALLOC_PAGES_MSG;
        m.vm_alloc_pages.num_pages = ALIGN_UP(length, PAGE_SIZE) / PAGE_SIZE;
        m.vm_alloc_pages.paddr = 0;
        ASSERT_OK(ipc_call(INIT_TASK, &m));
        ASSERT(m.type == VM_ALLOC_PAGES_REPLY_MSG);
        return (void *) m.vm_alloc_pages_reply.vaddr;
    }

    struct opened_file *f = lookup_fd(fd);
    ASSERT(f->embedded);
    return &f->embedded->data[offset];
}

void init_file_shims(void) {
    stdin = _REENT->_stdin;
    stdout = _REENT->_stdout;
    stderr = _REENT->_stderr;
}
