# GUI (Flutter)

```
static_library("flutter_engine_library_static") {
  visibility = [ ":*" ]
  output_name = "flutter_engine_static"
  complete_static_lib = true
  deps = [ ":embedder" ]
  public_configs = [ "//flutter:config" ]
}
```
