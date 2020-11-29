# GUI (Flutter)

```diff
diff --git a/shell/platform/embedder/BUILD.gn b/shell/platform/embedder/BUILD.gn
index 7868f0c14..bcb2c88ec 100644
--- a/shell/platform/embedder/BUILD.gn
+++ b/shell/platform/embedder/BUILD.gn
@@ -252,6 +252,24 @@ shared_library("flutter_engine_library") {
   public_configs = [ "//flutter:config" ]
 }

static_library("flutter_engine_library_static") {
  visibility = [ ":*" ]
  output_name = "flutter_engine_static"
  complete_static_lib = true
  deps = [ ":embedder", ":copy_headers", "//third_party/libcxx" ]
  public_configs = [ "//flutter:config" ]
}
```

```diff
diff --git a/build/config/BUILDCONFIG.gn b/build/config/BUILDCONFIG.gn
index 44c276c..614e43e 100644
--- a/build/config/BUILDCONFIG.gn
+++ b/build/config/BUILDCONFIG.gn
@@ -137,7 +137,7 @@ declare_args() {
   #   1 means minimal symbols, usually enough for backtraces only.
   #   0 means no symbols.
   #   -1 means auto-set (off in release, regular in debug).
-  symbol_level = -1
+  symbol_level = 2

   # Component build.
   is_component_build = false
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
+        "-fno-omit-frame-pointer",
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

## Debugging Notes
Since Flutter and its external dependencies (especially libcxx) have so many symbols, we cannot embed all of them into the symbol table.

When you examine the backtrace, use `dump2line.py` to get correct backtrace locations:

```
$ ./tools/dump2line.py --addr2line addr2line --image build/flutter.debug.elf
[flutter] WARN:     #0: 0000000001002179 pthread_cond_wait()+0x59
[flutter] WARN:     #1: 00000000010bcdc2 _ftello_r()+0x865cc
[flutter] WARN:     #2: 00000000010d7abb _ftello_r()+0xa12c5
[flutter] WARN:     #3: 00000000010d75de _ftello_r()+0xa0de8
[flutter] WARN:     #4: 00000000015dd839 _ftello_r()+0x5a7043
[flutter] WARN:     #5: 000000000108172e _ftello_r()+0x4af38
[flutter] WARN:     #6: 0000000001081536 _ftello_r()+0x4ad40
[flutter] WARN:     #7: 000000000106848c _ftello_r()+0x31c96
[flutter] WARN:     #8: 000000000106760e _ftello_r()+0x30e18
[flutter] WARN:     #9: 00000000010003e1 init()+0x251
[flutter] WARN:     #10: 000000000100016b main()+0x5b
[flutter] WARN:     #11: 00000000010066d7 resea_init()+0x57
[flutter] WARN:     #12: 000000000100e66b halt()+0x0
[Press Ctrl-D here to insert the EOF]
```
