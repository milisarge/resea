#ifndef __SYSCALL_H__
#define __SYSCALL_H__

#include <arch/syscall.h>
#include <types.h>

// System calls.
error_t ipc(tid_t dst, tid_t src, const void *m, void *r, uint32_t flags);
tid_t taskctl(tid_t tid, const char *name, vaddr_t ip, tid_t page, caps_t caps);
error_t irqctl(unsigned irq, bool enable);
int klogctl(char *buf, size_t buf_len, bool write);

// Wrapper functions.
tid_t task_create(tid_t tid, const char *name, vaddr_t ip, tid_t pager,
                  caps_t caps);
error_t task_destroy(tid_t tid);
void task_exit(void);
tid_t task_self(void);
void caps_drop(caps_t caps);
error_t ipc_send(tid_t dst, const void *m, size_t len);
error_t ipc_send_noblock(tid_t dst, const void *m, size_t len);
void ipc_reply(tid_t dst, const void *m, size_t len);
void ipc_reply_err(tid_t dst, error_t error);
struct message;
error_t ipc_recv(tid_t src, struct message *m, size_t max_len);
error_t ipc_call(tid_t dst, struct message *m, size_t send_len,
                 struct message *r, size_t recv_len);
error_t ipc_listen(tid_t dst);
error_t ipc_send_err(tid_t dst, error_t error);
error_t timer_set(msec_t timeout);
error_t irq_acquire(unsigned irq);
error_t irq_release(unsigned irq);
void klog_write(const char *str, int len);
int klog_read(char *buf, int len);

#endif
