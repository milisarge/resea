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

void init_file_shims(void) {
    stdin = _REENT->_stdin;
    stdout = _REENT->_stdout;
    stderr = _REENT->_stderr;
}
