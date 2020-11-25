name := flutter
description := A GUI server powered by Flutter
objs-y := main.o
external-objs-y := /home/seiya/flutter/src/out/linux_release_x64/obj/flutter/shell/platform/embedder/libflutter_engine_static.a
cflags-y := -I /home/seiya/flutter/src/out/linux_release_x64
