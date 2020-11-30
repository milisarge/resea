#include <resea/malloc.h>
#include <resea/task.h>
#include <resea/ipc.h>
#include <resea/async.h>
#include <elf/elf.h>
#include <string.h>
#include <message.h>
#include "task.h"
#include "mm.h"
#include "bootfs.h"

extern char __free_vaddr[];

static struct task tasks[CONFIG_NUM_TASKS];
static list_t services;

/// Look for the task in the our task table.
struct task *task_lookup(task_t tid) {
    if (tid <= 0 || tid > CONFIG_NUM_TASKS) {
        PANIC("invalid tid %d", tid);
    }

    struct task *task = &tasks[tid - 1];
    ASSERT(task->in_use);
    return task;
}

static void init_task_struct(struct task *task, struct vmspace *vmspace, const char *name,
    struct bootfs_file *file, void *file_header, struct elf64_ehdr *ehdr,
    const char *cmdline) {
    task->in_use = true;
    task->file = file;
    task->file_header = file_header;
    task->ehdr = ehdr;
    if (ehdr) {
        task->phdrs = (struct elf64_phdr *) ((uintptr_t) ehdr + ehdr->e_ehsize);
    } else {
        task->phdrs = NULL;
    }

    if (vmspace) {
        task->vmspace = vmspace;
        task->vmspace->ref_count++;
    } else {
        task->vmspace = malloc(sizeof(*task->vmspace));
        task->vmspace->free_vaddr = (vaddr_t) __free_vaddr;
        task->vmspace->ref_count = 0;
        list_init(&task->vmspace->page_areas);
    }

    task->ool_buf = 0;
    task->ool_len = 0;
    task->received_ool_buf = 0;
    task->received_ool_len = 0;
    task->received_ool_from = 0;
    list_init(&task->ool_sender_queue);
    list_nullify(&task->ool_sender_next);
    resea_strncpy(task->name, name, sizeof(task->name));
    resea_strncpy(task->cmdline, cmdline, sizeof(task->cmdline));
    resea_strncpy(task->waiting_for, "", sizeof(task->waiting_for));
    list_init(&task->watchers);
    memset(&task->thread_info, 0, sizeof(task->thread_info));
}

task_t task_spawn(struct bootfs_file *file, const char *cmdline, struct vmspace *vmspace, vaddr_t entry) {
    TRACE("launching %s...", file->name);

    // Look for an unused task ID.
    struct task *task = NULL;
    for (int i = 0; i < CONFIG_NUM_TASKS; i++) {
        if (!tasks[i].in_use) {
            task = &tasks[i];
            break;
        }
    }

    if (!task) {
        PANIC("too many tasks");
    }

    void *file_header = malloc(PAGE_SIZE);
    read_file(file, 0, file_header, PAGE_SIZE);

    // Ensure that it's an ELF file.
    struct elf64_ehdr *ehdr = (struct elf64_ehdr *) file_header;
    if (resea_memcmp(ehdr->e_ident, "\x7f" "ELF", 4) != 0) {
        WARN("%s: invalid ELF magic, ignoring...", file->name);
        return ERR_NOT_ACCEPTABLE;
    }

    if (!entry) {
        entry = ehdr->e_entry;
    }

    // Create a new task for the server.
    error_t err =
        task_create(task->tid, file->name, entry, task_self(), TASK_ALL_CAPS);
    ASSERT_OK(err);

    init_task_struct(task, vmspace, file->name, file, file_header, ehdr, cmdline);
    return task->tid;
}

task_t thread_spawn(struct task *roommate, vaddr_t entry, vaddr_t ip, vaddr_t sp, vaddr_t arg, vaddr_t tls) {
    task_t tid = task_spawn(roommate->file, "", roommate->vmspace, entry);
    struct task *task = task_lookup(tid);
    task->thread_info.sp = sp;
    task->thread_info.ip = ip;
    task->thread_info.arg = arg;
    task->thread_info.tls = tls;
    task->thread_info.task = tid;
    return tid;
}

task_t task_spawn_by_cmdline(const char *name_with_cmdline) {
    char *name = strdup(name_with_cmdline);

    // "echo hello world!" -> name="echo", cmdline="hello world!"
    char *cmdline = "";
    for (int i = 0; name[i] != '\0'; i++) {
        if (name[i] == ' ') {
            name[i] = '\0';
            cmdline = &name[i + 1];
            break;
        }
    }

    // Look for the executable in bootfs named `name`.
    struct bootfs_file *file;
    for (int i = 0; (file = bootfs_open(i)) != NULL; i++) {
        if (!resea_strcmp(file->name, name)) {
            break;
        }
    }

    if (!file) {
        return ERR_NOT_FOUND;
    }

    free(name);
    return task_spawn(file, cmdline, NULL, 0);
}

void task_kill(struct task *task) {
    LIST_FOR_EACH (w, &task->watchers, struct task_watcher, next) {
        struct message m;
        resea_bzero(&m, sizeof(m));
        m.type = TASK_EXITED_MSG;
        m.task_exited.task = task->tid;
        async_send(w->watcher->tid, &m);
        free(w);
    }

    LIST_FOR_EACH (service, &services, struct service, next) {
        if (service->task == task->tid) {
            list_remove(&service->next);
            free(service);
        }
    }

    task->vmspace->ref_count--;
    if (!task->vmspace->ref_count) {
        LIST_FOR_EACH(pa, &task->vmspace->page_areas, struct page_area, next) {
            free_page_area(pa);
        }

        free(task->vmspace);
    }

    task_destroy(task->tid);
    task->in_use = false;
    if (task->file_header) {
        free(task->file_header);
    }
}

void task_watch(struct task *watcher, struct task *task) {
    struct task_watcher *w = malloc(sizeof(*w));
    w->watcher = watcher;
    list_push_back(&task->watchers, &w->next);
}

void task_unwatch(struct task *watcher, struct task *task) {
    LIST_FOR_EACH (w, &task->watchers, struct task_watcher, next) {
        if (w->watcher == watcher) {
            list_remove(&w->next);
            free(w);
            return;
        }
    }
}

void service_register(struct task *task, const char *name) {
    // Add the server into the service list.
    struct service *service = malloc(sizeof(*service));
    service->task = task->tid;
    resea_strncpy(service->name, name, sizeof(service->name));
    list_nullify(&service->next);
    list_push_back(&services, &service->next);

    // Look for tasks waiting for the service...
    for (int i = 0; i < CONFIG_NUM_TASKS; i++) {
        struct task *task = &tasks[i];
        if (!resea_strcmp(task->waiting_for, name)) {
            struct message m;
            resea_bzero(&m, sizeof(m));

            m.type = DISCOVERY_LOOKUP_REPLY_MSG;
            m.discovery_lookup_reply.task = service->task;
            ipc_reply(task->tid, &m);

            // The task no longer wait for the service. Clear the field.
            resea_strncpy(task->waiting_for, "", sizeof(task->waiting_for));
        }
    }
}

task_t service_wait(struct task *task, const char *name) {
    LIST_FOR_EACH (s, &services, struct service, next) {
        if (!resea_strcmp(s->name, name)) {
            return s->task;
        }
    }

    // The service is not yet available. Block the caller task until the
    // server is registered by `ipc_serve()`.
    resea_strncpy(task->waiting_for, name, sizeof(task->waiting_for));
    return ERR_WOULD_BLOCK;
}

void service_warn_deadlocked_tasks(void) {
    for (int i = 0; i < CONFIG_NUM_TASKS; i++) {
        struct task *task = &tasks[i];
        if (strlen(task->waiting_for) > 0) {
            WARN(
                "%s still waiting for a missing service '%s', "
                "did you forgot to enable a server in the build config?",
                task->name, task->waiting_for
            );
        }
    }
}

struct task *vm_task = NULL;

void task_init(void) {
    for (int i = 0; i < CONFIG_NUM_TASKS; i++) {
        tasks[i].in_use = false;
        tasks[i].tid = i + 1;
    }

    // Initialize a task struct for myself.
    vm_task = &tasks[INIT_TASK - 1];
    init_task_struct(vm_task, NULL, "vm", NULL, NULL, NULL, "");
    list_init(&services);
}
