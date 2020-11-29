#include <resea/ipc.h>
#include <resea/printf.h>
#include <string.h>

void init(void);
void init_file_shims(void);

void main(void) {
    TRACE("starting...");

    INFO("ready");
    init_file_shims();
    init();
    INFO("successfully initialized flutter!");
}
