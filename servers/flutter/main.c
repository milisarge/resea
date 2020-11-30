#include <resea/ipc.h>
#include <resea/printf.h>
#include <string.h>

void init(void);
void init_file_shims(void);
void init_pthread_shims(void);

#include <elf/elf.h>
extern uint8_t __app_so[];

uint8_t *kDartVmSnapshotInstructions = NULL;
uint8_t *kDartVmSnapshotData = NULL;
uint8_t *kDartIsolateSnapshotInstructions = NULL;
uint8_t *kDartIsolateSnapshotData = NULL;

void parse_app_so(void) {
    struct elf64_ehdr *ehdr = (struct elf64_ehdr *) __app_so;
    struct elf64_shdr *shdrs = (struct elf64_shdr *) &__app_so[ehdr->e_shoff];
    struct elf64_shdr *dynsym = NULL;
    for (uint64_t i = 0; i < ehdr->e_shnum; i++) {
        struct elf64_shdr *shdr = &shdrs[i];
        if (shdr->sh_type == SHT_DYNSYM) {
            dynsym = shdr;
            break;
        }
    }

    ASSERT(dynsym != NULL);
    ASSERT(dynsym->sh_link < ehdr->e_shnum);

    struct elf64_sym *symbols = (struct elf64_sym *) &__app_so[dynsym->sh_offset];
    struct elf64_shdr *dynstr = &shdrs[dynsym->sh_link];
    const char *strtab = (const char *) &__app_so[dynstr->sh_offset];
    for (uint64_t i = 0; i < dynsym->sh_entsize; i++) {
        struct elf64_sym *sym = &symbols[i];
        if (ELF64_ST_TYPE(sym->st_info) != STT_FUNC) {
            continue;
        }

        const char *name = &strtab[sym->st_name];
        uint8_t *data = &__app_so[sym->st_value];
        TRACE("app.so: offset=%p, symbol=%s", sym->st_value, name);

        if (!strcmp(name, "_kDartVmSnapshotInstructions")) {
            kDartVmSnapshotInstructions = data;
            continue;
        }
        if (!strcmp(name, "_kDartVmSnapshotData")) {
            kDartVmSnapshotData = data;
            continue;
        }
        if (!strcmp(name, "_kDartIsolateSnapshotInstructions")) {
            kDartIsolateSnapshotInstructions = data;
            continue;
        }
        if (!strcmp(name, "_kDartIsolateSnapshotData")) {
            kDartIsolateSnapshotData = data;
            continue;
        }
    }
}

void main(void) {
    TRACE("starting...");

    INFO("ready");
    init_file_shims();
    init_pthread_shims();
    parse_app_so();
    PANIC("exit");
    init();
    INFO("successfully initialized flutter!");
}
