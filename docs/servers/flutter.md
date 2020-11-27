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

```diff
diff --git a/build/config/compiler/BUILD.gn b/build/config/compiler/BUILD.gn
index 5f299d7..470617f 100644
--- a/build/config/compiler/BUILD.gn
+++ b/build/config/compiler/BUILD.gn
@@ -97,8 +97,7 @@ config("compiler") {
       cflags += [ "-fstack-protector-all" ]
     } else if (is_linux) {
       cflags += [
-        "-fstack-protector",
-        "--param=ssp-buffer-size=4",
+        "-fno-stack-protector",
       ]
     }
```

```
./flutter/tools/gn --clang --lto --embedder-for-target --target-os linux --linux-cpu x64 --runtime-mode release --no-stripped --no-goma
```

```
~/newlib-4.0.0/build
$ ../newlib/configure --disable-multilib --disable-shared --target=x86_64-elf --disable-newlib-supplied-syscalls CFLAGS="-D_FORTIFY_SOURCE=0 -fno-stack-protector"
```
