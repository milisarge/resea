#include <config.h>
#include <resea/ipc.h>
#include <resea/printf.h>

void main(void) {
    INFO("starting IPC benchmark...");
    ipc_serve("benchmark_server");

    struct message m;
    struct message r = { .type = BENCHMARK_NOP_REPLY_MSG };
    ipc_recv(IPC_ANY, &m);
    while (true) {
        ipc_replyrecv(m.src, &r);
    }
}
