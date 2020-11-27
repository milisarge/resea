#include <resea/ipc.h>
#include <resea/printf.h>
#include <string.h>

void init(void);
void init_shims(void);
void main(void) {
    TRACE("starting...");

    INFO("ready");
    init_shims();
    init();
    PANIC("returned from flutter!");
}
