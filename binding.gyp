{
    "targets": [{
        "target_name": "ckmeans",
        "sources": [
            "./src/native/napi_ckmeans.c"
        ],
        "include_dirs": [
          "<!@(node -p \"require('node-addon-api').include\")"
        ],
         "cflags": [
           "-Wall",
           "-Wno-implicit-fallthrough",
           "-Wno-maybe-uninitialized",
           "-Wno-uninitialized",
           "-Wno-unused-function",
           "-Wextra",
           "-O3"
         ],
         "cflags_c": [
           "-std=c99"
         ],
        "defines": [ "NAPI_DISABLE_CPP_EXCEPTIONS" ]
    }]
}