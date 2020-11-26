#include <resea/ipc.h>
#include <resea/printf.h>
#include <string.h>

void init(void);

void main(void) {
    TRACE("starting...");

    INFO("ready");
    init();
    while (true) {
        struct message m;
        bzero(&m, sizeof(m));
        ASSERT_OK(ipc_recv(IPC_ANY, &m));

        switch (m.type) {
            default:
                TRACE("unknown message %d", m.type);
        }
    }
}
