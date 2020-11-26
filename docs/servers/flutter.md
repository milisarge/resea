# GUI (Flutter)

```
static_library("flutter_engine_library_static") {
  visibility = [ ":*" ]
  output_name = "flutter_engine_static"
  complete_static_lib = true
  deps = [ ":embedder", "//third_party/libcxx" ]
  public_configs = [ "//flutter:config" ]
}
```

```
./flutter/tools/gn --clang --lto --embedder-for-target --target-os linux --linux-cpu x64 --runtime-mode release --no-stripped --no-goma
```

```
~/newlib-4.0.0/build
$ ../newlib/configure --disable-multilib --disable-shared --target=x86_64-elf --disable-newlib-supplied-syscalls CFLAGS="-D_FORTIFY_SOURCE=0"
```
