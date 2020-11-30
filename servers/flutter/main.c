#include <resea/ipc.h>
#include <resea/printf.h>
#include <string.h>

void init(void);
void init_file_shims(void);
void init_pthread_shims(void);

#include <elf/elf.h>
extern uint8_t __app_so[];

uint8_t *kDartVmSnapshotInstructions = NULL;
size_t kDartVmSnapshotInstructionsSize = 0;
uint8_t *kDartVmSnapshotData = NULL;
size_t kDartVmSnapshotDataSize = 0;
uint8_t *kDartIsolateSnapshotInstructions = NULL;
size_t kDartIsolateSnapshotInstructionsSize = 0;
uint8_t *kDartIsolateSnapshotData = NULL;
size_t kDartIsolateSnapshotDataSize = 0;

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
        TRACE("app.so: offset=%p, size=%p, symbol=%s", sym->st_value, sym->st_size, name);

        if (!strcmp(name, "_kDartVmSnapshotInstructions")) {
            kDartVmSnapshotInstructions = data;
            kDartVmSnapshotInstructionsSize = sym->st_size;
            continue;
        }
        if (!strcmp(name, "_kDartVmSnapshotData")) {
            kDartVmSnapshotData = data;
            kDartVmSnapshotDataSize = sym->st_size;
            continue;
        }
        if (!strcmp(name, "_kDartIsolateSnapshotInstructions")) {
            kDartIsolateSnapshotInstructions = data;
            kDartIsolateSnapshotInstructionsSize = sym->st_size;
            continue;
        }
        if (!strcmp(name, "_kDartIsolateSnapshotData")) {
            kDartIsolateSnapshotData = data;
            kDartIsolateSnapshotDataSize = sym->st_size;
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
    init();
    INFO("successfully initialized flutter!");
}
