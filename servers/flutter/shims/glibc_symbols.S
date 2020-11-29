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
