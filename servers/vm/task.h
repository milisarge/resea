#ifndef __TASK_H__
#define __TASK_H__

#include <types.h>
#include <list.h>

#define SERVICE_NAME_LEN 32

struct vmspace {
    int ref_count;
    vaddr_t free_vaddr;
    list_t page_areas;
};

/// Task Control Block (TCB).
struct task {
    bool in_use;
    task_t tid;
    char name[32];
    char cmdline[512];
    struct bootfs_file *file;
    void *file_header;
    struct elf64_ehdr *ehdr;
    struct elf64_phdr *phdrs;
    struct vmspace *vmspace;
    vaddr_t ool_buf;
    size_t ool_len;
    task_t received_ool_from;
    vaddr_t received_ool_buf;
    size_t received_ool_len;
    list_t ool_sender_queue;
    list_elem_t ool_sender_next;
    struct message ool_sender_m;
    char waiting_for[SERVICE_NAME_LEN];
    list_t watchers;

    __packed struct {
        vaddr_t sp;
        vaddr_t arg;
    } thread_info;
};

struct service {
    list_elem_t next;
    char name[SERVICE_NAME_LEN];
    task_t task;
};

struct task_watcher {
    list_elem_t next;
    struct task *watcher;
};

extern struct task *vm_task;

task_t task_spawn(struct bootfs_file *file, const char *cmdline, struct vmspace *vmspace, vaddr_t entry);
task_t thread_spawn(struct task *roommate, vaddr_t entry, vaddr_t sp, vaddr_t arg);
task_t task_spawn_by_cmdline(const char *name_with_cmdline);
struct task *task_lookup(task_t tid);
void task_kill(struct task *task);
void task_watch(struct task *watcher, struct task *task);
void task_unwatch(struct task *watcher, struct task *task);
void service_register(struct task *task, const char *name);
task_t service_wait(struct task *task, const char *name);
void service_warn_deadlocked_tasks(void);
void task_init(void);

#endif
