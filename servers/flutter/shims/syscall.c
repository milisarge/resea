#include <resea/printf.h>

// Linux syscall.
long syscall(long n) {
    INFO("syscall n = %d", n);
    if (n == 186) {
        // gettid
        return 1;
    }

    return 0;
}

