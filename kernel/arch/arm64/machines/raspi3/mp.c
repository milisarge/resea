#include <printk.h>
#include <machine/machine.h>
#include <machine/peripherals.h>

#define NUM_CPUS 2

extern char boot[];

void machine_mp_start(void) {
    for (int cpu = 1; cpu < NUM_CPUS; cpu++) {
        TRACE("Booting CPU #%d...", cpu);
        TRACE("(uint32_t) boot = %p", (uint32_t) boot);
        mmio_write(MAILBOX3_SET(cpu), (uint32_t) boot);

        // https://leiradel.github.io/2019/01/20/Raspberry-Pi-Stubs.html
        paddr_t paddr = 0xd8 + cpu * 8;
        *((volatile uint32_t *) from_paddr(paddr)) = (uint32_t) boot;

        __asm__ __volatile__("dsb sy" ::: "memory");
        __asm__ __volatile__("sev");
    }
}
