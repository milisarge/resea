name := flutter
description := A GUI server powered by Flutter
objs-y := main.o flutter_engine.o app.o
libs-y := elf
subdirs-y := shims

SYSROOT_DIR := ~/src/flutter/mysdk/sysroot

flutter_build := linux_release_x64

external-objs-y := \
	/home/seiya/flutter/src/out/$(flutter_build)/obj/flutter/shell/platform/embedder/libflutter_engine_static2.a \
	/home/seiya/newlib-4.0.0/build/libc.a \
	/home/seiya/newlib-4.0.0/build/libm.a

cflags-y := \
	-I/home/seiya/flutter/src/build/linux/debian_sid_arm64-sysroot/usr/lib/gcc/aarch64-linux-gnu/7/include \
	-I/home/seiya/flutter/src/out/$(flutter_build) \
	-DICU_DATA_FILE='"/home/seiya/flutter/src/out/$(flutter_build)/icudtl.dat"' \
	-DAPP_SO='"/home/seiya/hello-from-flutter/myapp/build/app.so"'
