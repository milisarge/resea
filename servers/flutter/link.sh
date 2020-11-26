#!/bin/bash

libs=(
    ~/flutter/src/out/linux_release_x64/obj/flutter/shell/platform/embedder/libflutter_engine_static.a
)

ld.lld \
    -o flutter.bin \
    ${libs[@]}
