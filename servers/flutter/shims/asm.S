.intel_syntax noprefix
.text

.macro glibc_wrapper, name
.global \name@GLIBC_2.2.5
\name@GLIBC_2.2.5:
    call \name
    ret
.endm

glibc_wrapper log
glibc_wrapper log2f
glibc_wrapper pow
glibc_wrapper powf
glibc_wrapper exp
glibc_wrapper expf
glibc_wrapper exp2f


.global pthread_thread_entry
pthread_thread_entry:
    // __packed struct {
    //     vaddr_t ip;
    //     vaddr_t sp;
    //     vaddr_t arg;
    //     vaddr_t tls;
    //     task_t task;
    // } thread_info;
    mov rbp, 0
    mov rsp, [__thread_info + 8]

    mov rdi, [__thread_info + 24]
    call pthread_before_start_routine

    mov rax, [__thread_info + 0]
    mov rdi, [__thread_info + 16]
    call rax
    ud2
