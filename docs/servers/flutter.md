# GUI (Flutter)

```diff
diff --git a/shell/platform/embedder/BUILD.gn b/shell/platform/embedder/BUILD.gn
index 7868f0c14..bcb2c88ec 100644
--- a/shell/platform/embedder/BUILD.gn
+++ b/shell/platform/embedder/BUILD.gn
@@ -252,6 +252,24 @@ shared_library("flutter_engine_library") {
   public_configs = [ "//flutter:config" ]
 }

+static_library("flutter_engine_library_static") {
+  visibility = [ ":*" ]
+  output_name = "flutter_engine_static"
+  complete_static_lib = true
+  deps = [ ":embedder", ":copy_headers", "//third_party/libcxx" ]
+  public_configs = [ "//flutter:config" ]
+}
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

# `.gclient_entries`
```
entries = {
  'src/flutter': 'https://github.com/flutter/engine.git',
  'src': 'https://github.com/flutter/buildroot.git@4985b584a430ea3fda9433dccafa5047531e0974',
  'src/buildtools/linux-x64/clang:fuchsia/third_party/clang/${platform}': 'https://chrome-infra-packages.appspot.com/fuchsia/third_party/clang/${platform}@git_revision:7e9747b50bcb1be28d4a3236571e8050835497a6',
  'src/flutter/third_party/gn:gn/gn/${platform}': 'https://chrome-infra-packages.appspot.com/gn/gn/${platform}@git_revision:1e3fd10c5df6b704fc764ee388149e4f32862823',
  'src/fuchsia/sdk/linux:fuchsia/sdk/core/linux-amd64': 'https://chrome-infra-packages.appspot.com/fuchsia/sdk/core/linux-amd64@eyiA9UhTGepareJhbCRXoahHoMFLM2pf10ei1Mi0DZ0C',
  'src/fuchsia/toolchain/linux:fuchsia/clang/linux-amd64': 'https://chrome-infra-packages.appspot.com/fuchsia/clang/linux-amd64@OT6p30bQQhyCzRSy7xPsSbZ88J3PWOnneenkMZ0j7kIC',
  'src/ios_tools': 'https://chromium.googlesource.com/chromium/src/ios.git@69b7c1b160e7107a6a98d948363772dc9caea46f',
  'src/third_party/abseil-cpp': 'https://chromium.googlesource.com/chromium/src/third_party/abseil-cpp.git@2d8c1340f0350828f1287c4eaeebefcf317bcfc9',
  'src/third_party/android_embedding_dependencies:flutter/android/embedding_bundle': 'https://chrome-infra-packages.appspot.com/flutter/android/embedding_bundle@last_updated:2020-09-11T17:57:41-0700',
  'src/third_party/android_tools/google-java-format:flutter/android/google-java-format': 'https://chrome-infra-packages.appspot.com/flutter/android/google-java-format@version:1.7-1',
  'src/third_party/android_tools/ndk:flutter/android/ndk/${platform}': 'https://chrome-infra-packages.appspot.com/flutter/android/ndk/${platform}@version:r21.0.6113669',
  'src/third_party/android_tools/sdk/build-tools:flutter/android/sdk/build-tools/${platform}': 'https://chrome-infra-packages.appspot.com/flutter/android/sdk/build-tools/${platform}@version:30.0.1',
  'src/third_party/android_tools/sdk/licenses:flutter/android/sdk/licenses': 'https://chrome-infra-packages.appspot.com/flutter/android/sdk/licenses@latest',
  'src/third_party/android_tools/sdk/platform-tools:flutter/android/sdk/platform-tools/${platform}': 'https://chrome-infra-packages.appspot.com/flutter/android/sdk/platform-tools/${platform}@version:30.0.4',
  'src/third_party/android_tools/sdk/platforms:flutter/android/sdk/platforms': 'https://chrome-infra-packages.appspot.com/flutter/android/sdk/platforms@version:30r3',
  'src/third_party/android_tools/sdk/tools:flutter/android/sdk/tools/${platform}': 'https://chrome-infra-packages.appspot.com/flutter/android/sdk/tools/${platform}@version:26.1.1',
  'src/third_party/angle': 'https://github.com/google/angle.git@ed90c9917b1b7fc6def319184b10609c11b2bd84',
  'src/third_party/angle/third_party/vulkan-headers/src': 'https://fuchsia.googlesource.com/third_party/Vulkan-Headers.git@5de4e8fab88ef0bd6994d9ddbcc864e3179b9e79',
  'src/third_party/benchmark': 'https://fuchsia.googlesource.com/third_party/benchmark@a779ffce872b4c811beef482e18bd0b63626aa42',
  'src/third_party/boringssl': 'https://github.com/dart-lang/boringssl_gen.git@429ccb1877f7987a6f3988228bc2440e61293499',
  'src/third_party/boringssl/src': 'https://boringssl.googlesource.com/boringssl.git@4dfd5af70191b068aebe567b8e29ce108cee85ce',
  'src/third_party/colorama/src': 'https://chromium.googlesource.com/external/colorama.git@799604a1041e9b3bc5d2789ecbd7e8db2e18e6b8',
  'src/third_party/dart': 'https://dart.googlesource.com/sdk.git@cd7b857e70a7eb9da62694024f96d1cb3a90d31b',
  'src/third_party/dart/third_party/pkg/args': 'https://dart.googlesource.com/args.git@1.6.0',
  'src/third_party/dart/third_party/pkg/async': 'https://dart.googlesource.com/async.git@695b3ac280f107c84adf7488743abfdfaaeea68f',
  'src/third_party/dart/third_party/pkg/bazel_worker': 'https://dart.googlesource.com/bazel_worker.git@060c55a933d39798681a4f533b161b81dc48d77e',
  'src/third_party/dart/third_party/pkg/boolean_selector': 'https://dart.googlesource.com/boolean_selector.git@665e6921ab246569420376f827bff4585dff0b14',
  'src/third_party/dart/third_party/pkg/charcode': 'https://dart.googlesource.com/charcode.git@bcd8a12c315b7a83390e4865ad847ecd9344cba2',
  'src/third_party/dart/third_party/pkg/cli_util': 'https://dart.googlesource.com/cli_util.git@50cc840b146615899e97b892578848401b2028d5',
  'src/third_party/dart/third_party/pkg/clock': 'https://dart.googlesource.com/clock.git@a494269254ba978e7ef8f192c5f7fec3fc05b9d3',
  'src/third_party/dart/third_party/pkg/collection': 'https://dart.googlesource.com/collection.git@e4bb038ce2d8e66fb15818aa40685c68d53692ab',
  'src/third_party/dart/third_party/pkg/convert': 'https://dart.googlesource.com/convert.git@dd3bd28f63be7cb8ab961f38bc73229e4473b555',
  'src/third_party/dart/third_party/pkg/crypto': 'https://dart.googlesource.com/crypto.git@f7c48b334b1386bc5ab0f706fbcd6df8496a87fc',
  'src/third_party/dart/third_party/pkg/csslib': 'https://dart.googlesource.com/csslib.git@6f77b3dcee957d3e2d5083f666221a220e9ed1f1',
  'src/third_party/dart/third_party/pkg/dart2js_info': 'https://dart.googlesource.com/dart2js_info.git@83504e459e13862cc6a61c147147ef7892a0d285',
  'src/third_party/dart/third_party/pkg/dartdoc': 'https://dart.googlesource.com/dartdoc.git@d79877d0764ce23ffea7055049f8da5dffce0308',
  'src/third_party/dart/third_party/pkg/ffi': 'https://dart.googlesource.com/ffi.git@a5d4232cd38562c75a3ed847baa340e399538028',
  'src/third_party/dart/third_party/pkg/fixnum': 'https://dart.googlesource.com/fixnum.git@16d3890c6dc82ca629659da1934e412292508bba',
  'src/third_party/dart/third_party/pkg/glob': 'https://dart.googlesource.com/glob.git@e9f4e6b7ae8abe5071461cf8f47191bb19cf7ef6',
  'src/third_party/dart/third_party/pkg/html': 'https://dart.googlesource.com/html.git@22f17e97fedeacaa1e945cf84d8016284eed33a6',
  'src/third_party/dart/third_party/pkg/http': 'https://dart.googlesource.com/http.git@1617b728fc48f64fb0ed7dc16078c03adcc64179',
  'src/third_party/dart/third_party/pkg/http_multi_server': 'https://dart.googlesource.com/http_multi_server.git@f1d1c9c024a293ab0a0e16f8b7632e87c708b448',
  'src/third_party/dart/third_party/pkg/http_parser': 'https://dart.googlesource.com/http_parser.git@5dd4d16693242049dfb43b5efa429fedbf932e98',
  'src/third_party/dart/third_party/pkg/http_retry': 'https://dart.googlesource.com/http_retry.git@0.1.1',
  'src/third_party/dart/third_party/pkg/http_throttle': 'https://dart.googlesource.com/http_throttle.git@1.0.2',
  'src/third_party/dart/third_party/pkg/intl': 'https://dart.googlesource.com/intl.git@0.17.0-nullsafety',
  'src/third_party/dart/third_party/pkg/json_rpc_2': 'https://dart.googlesource.com/json_rpc_2.git@b8dfe403fd8528fd14399dee3a6527b55802dd4d',
  'src/third_party/dart/third_party/pkg/linter': 'https://dart.googlesource.com/linter.git@0.1.125',
  'src/third_party/dart/third_party/pkg/logging': 'https://dart.googlesource.com/logging.git@e2f633b543ef89c54688554b15ca3d7e425b86a2',
  'src/third_party/dart/third_party/pkg/markdown': 'https://dart.googlesource.com/markdown.git@6f89681d59541ddb1cf3a58efbdaa2304ffc3f51',
  'src/third_party/dart/third_party/pkg/matcher': 'https://dart.googlesource.com/matcher.git@9cae8faa7868bf3a88a7ba45eb0bd128e66ac515',
  'src/third_party/dart/third_party/pkg/mime': 'https://dart.googlesource.com/mime.git@07635f7774447503248fbc6afb3911e9000a477e',
  'src/third_party/dart/third_party/pkg/mockito': 'https://dart.googlesource.com/mockito.git@d39ac507483b9891165e422ec98d9fb480037c8b',
  'src/third_party/dart/third_party/pkg/mustache': 'https://dart.googlesource.com/external/github.com/xxgreg/mustache@664737ecad027e6b96d0d1e627257efa0e46fcb1',
  'src/third_party/dart/third_party/pkg/oauth2': 'https://dart.googlesource.com/oauth2.git@1.6.0',
  'src/third_party/dart/third_party/pkg/path': 'https://dart.googlesource.com/path.git@62ecd5a78ffe5734d14ed0df76d20309084cd04a',
  'src/third_party/dart/third_party/pkg/pedantic': 'https://dart.googlesource.com/pedantic.git@a884ea2db943b8756cc94385990bd750aec06928',
  'src/third_party/dart/third_party/pkg/pool': 'https://dart.googlesource.com/pool.git@eedbd5fde84f9a1a8da643b475305a81841da599',
  'src/third_party/dart/third_party/pkg/protobuf': 'https://dart.googlesource.com/protobuf.git@0d03fd588df69e9863e2a2efc0059dee8f18d5b2',
  'src/third_party/dart/third_party/pkg/pub': 'https://dart.googlesource.com/pub.git@228e69e53862879c283c42b98086aa7536012a66',
  'src/third_party/dart/third_party/pkg/pub_semver': 'https://dart.googlesource.com/pub_semver.git@10569a1e867e909cf5db201f73118020453e5db8',
  'src/third_party/dart/third_party/pkg/resource': 'https://dart.googlesource.com/resource.git@6b79867d0becf5395e5819a75720963b8298e9a7',
  'src/third_party/dart/third_party/pkg/shelf': 'https://dart.googlesource.com/shelf.git@289309adc6c39aab0a63db676d550c517fc1cc2d',
  'src/third_party/dart/third_party/pkg/shelf_packages_handler': 'https://dart.googlesource.com/shelf_packages_handler.git@2.0.0',
  'src/third_party/dart/third_party/pkg/shelf_proxy': 'https://dart.googlesource.com/shelf_proxy.git@0.1.0+7',
  'src/third_party/dart/third_party/pkg/shelf_static': 'https://dart.googlesource.com/shelf_static.git@a6168f162df88b0eef7e328629bf020122d5039e',
  'src/third_party/dart/third_party/pkg/shelf_web_socket': 'https://dart.googlesource.com/shelf_web_socket.git@8050a55b16faa5052a3e5d7dcdc170c59b6644f2',
  'src/third_party/dart/third_party/pkg/source_map_stack_trace': 'https://dart.googlesource.com/source_map_stack_trace.git@1c3026f69d9771acf2f8c176a1ab750463309cce',
  'src/third_party/dart/third_party/pkg/source_maps': 'https://dart.googlesource.com/source_maps.git@53eb92ccfe6e64924054f83038a534b959b12b3e',
  'src/third_party/dart/third_party/pkg/source_span': 'https://dart.googlesource.com/source_span.git@49ff31eabebed0da0ae6634124f8ba5c6fbf57f1',
  'src/third_party/dart/third_party/pkg/sse': 'https://dart.googlesource.com/sse.git@9a486d058a17e880afa9cc1c3c0dd8bad726bcbc',
  'src/third_party/dart/third_party/pkg/stack_trace': 'https://dart.googlesource.com/stack_trace.git@6788afc61875079b71b3d1c3e65aeaa6a25cbc2f',
  'src/third_party/dart/third_party/pkg/stagehand': 'https://dart.googlesource.com/stagehand.git@v3.3.11',
  'src/third_party/dart/third_party/pkg/stream_channel': 'https://dart.googlesource.com/stream_channel.git@d7251e61253ec389ee6e045ee1042311bced8f1d',
  'src/third_party/dart/third_party/pkg/string_scanner': 'https://dart.googlesource.com/string_scanner.git@1b63e6e5db5933d7be0a45da6e1129fe00262734',
  'src/third_party/dart/third_party/pkg/term_glyph': 'https://dart.googlesource.com/term_glyph.git@6a0f9b6fb645ba75e7a00a4e20072678327a0347',
  'src/third_party/dart/third_party/pkg/test': 'https://dart.googlesource.com/test.git@e37a93bbeae23b215972d1659ac865d71287ff6a',
  'src/third_party/dart/third_party/pkg/test_reflective_loader': 'https://dart.googlesource.com/test_reflective_loader.git@0.1.9',
  'src/third_party/dart/third_party/pkg/typed_data': 'https://dart.googlesource.com/typed_data.git@f94fc57b8e8c0e4fe4ff6cfd8290b94af52d3719',
  'src/third_party/dart/third_party/pkg/usage': 'https://dart.googlesource.com/usage.git@16fbfd90c58f16e016a295a880bc722d2547d2c9',
  'src/third_party/dart/third_party/pkg/watcher': 'https://dart.googlesource.com/watcher.git@64e254eba16f56d41f10d72c0b1cb24e130e1f8b',
  'src/third_party/dart/third_party/pkg/web_socket_channel': 'https://dart.googlesource.com/web_socket_channel.git@490061ef0e22d3c8460ad2802f9948219365ad6b',
  'src/third_party/dart/third_party/pkg/yaml': 'https://dart.googlesource.com/yaml.git@cca02c9e4f6826d62644901ed65c6d72b90a0713',
  'src/third_party/dart/third_party/pkg_tested/dart_style': 'https://dart.googlesource.com/dart_style.git@1.3.10',
  'src/third_party/dart/third_party/pkg_tested/package_config': 'https://dart.googlesource.com/package_config.git@9c586d04bd26fef01215fd10e7ab96a3050cfa64',
  'src/third_party/dart/tools/sdks:dart/dart-sdk/${platform}': 'https://chrome-infra-packages.appspot.com/dart/dart-sdk/${platform}@version:2.12.0-0.0.dev',
  'src/third_party/fontconfig/src': 'https://chromium.googlesource.com/external/fontconfig.git@c336b8471877371f0190ba06f7547c54e2b890ba',
  'src/third_party/freetype2': 'https://fuchsia.googlesource.com/third_party/freetype2@edab12c07ac05d1185616688f338b1ad15936796',
  'src/third_party/glfw': 'https://fuchsia.googlesource.com/third_party/glfw@999f3556fdd80983b10051746264489f2cb1ef16',
  'src/third_party/googletest': 'https://fuchsia.googlesource.com/third_party/googletest@3fef9015bfe7617d57806cd7c73a653b28559fae',
  'src/third_party/gyp': 'https://chromium.googlesource.com/external/gyp.git@4801a5331ae62da9769a327f11c4213d32fb0dad',
  'src/third_party/harfbuzz': 'https://fuchsia.googlesource.com/third_party/harfbuzz@9c55f4cf3313d68d68f68419e7a57fb0771fcf49',
  'src/third_party/icu': 'https://chromium.googlesource.com/chromium/deps/icu.git@c2a4cae149aae7fd30c4cbe3cf1b30df03b386f1',
  'src/third_party/khronos': 'https://chromium.googlesource.com/chromium/src/third_party/khronos.git@7122230e90547962e0f0c627f62eeed3c701f275',
  'src/third_party/libcxx': 'https://fuchsia.googlesource.com/third_party/libcxx@7524ef50093a376f334a62a7e5cebf5d238d4c99',
  'src/third_party/libcxxabi': 'https://fuchsia.googlesource.com/third_party/libcxxabi@74d1e602c76350f0760bf6907910e4f3a4fccffe',
  'src/third_party/libjpeg-turbo': 'https://fuchsia.googlesource.com/third_party/libjpeg-turbo@0fb821f3b2e570b2783a94ccd9a2fb1f4916ae9f',
  'src/third_party/libwebp': 'https://chromium.googlesource.com/webm/libwebp.git@0.6.0',
  'src/third_party/ocmock': 'https://github.com/erikdoe/ocmock.git@v3.7.1',
  'src/third_party/pkg/when': 'https://dart.googlesource.com/when.git@0.2.0',
  'src/third_party/rapidjson': 'https://fuchsia.googlesource.com/third_party/rapidjson@ef3564c5c8824989393b87df25355baf35ff544b',
  'src/third_party/root_certificates': 'https://dart.googlesource.com/root_certificates.git@7e5ec82c99677a2e5b95ce296c4d68b0d3378ed8',
  'src/third_party/skia': 'https://skia.googlesource.com/skia.git@36d06a806f69438192a19395ea522116e8e94b01',
  'src/third_party/swiftshader': 'https://swiftshader.googlesource.com/SwiftShader.git@5d1e8540407c138f47028d64684f3da599430aa4',
  'src/third_party/vulkan': 'https://github.com/KhronosGroup/Vulkan-Docs.git@v1.1.91',
  'src/third_party/wuffs': 'https://skia.googlesource.com/external/github.com/google/wuffs.git@00cc8a50aa0c86b6bcb37e9ece8fb100047cc17b',
}
```
