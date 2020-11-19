#include "../../machine.h"
#include <machine/peripherals.h>
#include <printk.h>

#define NUM_CPUS 4

extern char boot[];

void machine_mp_start(void) {
    for (int cpu = 1; cpu < NUM_CPUS; cpu++) {
        TRACE("Booting CPU #%d...", cpu);
        mmio_write(MAILBOX3_SET(cpu), (uint32_t) boot);
    }
}
