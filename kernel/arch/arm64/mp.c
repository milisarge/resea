#include <task.h>
#include <machine/machine.h>
#include "asm.h"

static struct cpuvar cpuvars[NUM_CPUS_MAX];

struct cpuvar *arm64_get_cpuvar(void) {
    return &cpuvars[mp_self()];
}


void halt(void) {
    while (true) {
        __asm__ __volatile__("wfi");
    }
}

void mp_start(void) {
    machine_mp_start();
}

void mp_reschedule(void) {
    // Do nothing: we don't support multiprocessors.
}

void lock(void) {
    // TODO:
}

void panic_lock(void) {
    // TODO:
}

void unlock(void) {
    // TODO:
}

void panic_unlock(void) {
    // TODO:
}
