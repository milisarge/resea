#include <flutter_embedder.h>

void _init();

typedef void (*ctor_func_t)(void);
extern ctor_func_t __preinit_array[];
extern ctor_func_t __preinit_array_end[];
extern ctor_func_t __init_array[];
extern ctor_func_t __init_array_end[];

static void call_ctors(void) {
    for (ctor_func_t *f = __preinit_array; f != __preinit_array_end; f++) {
        (*f)();
    }

    for (ctor_func_t *f = __init_array; f != __init_array_end; f++) {
        (*f)();
    }
}

void init(void) {
    call_ctors();
    FlutterEngineRun(0, NULL, NULL, NULL, NULL);
}
