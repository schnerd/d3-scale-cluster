#include <node_api.h>
#include "./common.h"
#include "./ckmeans.c"
napi_value MyFunction(napi_env env, napi_callback_info info) {
    size_t argc = 2;
    napi_value args[2];
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, NULL, NULL));

    NAPI_ASSERT(env, argc == 2, "Wrong number of arguments");

    napi_valuetype valuetype0;
    NAPI_CALL(env, napi_typeof(env, args[0], &valuetype0));

    NAPI_ASSERT(env, valuetype0 == napi_object, "Wrong type of arguments. Expects typed array as first argument");

    napi_value input_array = args[0];
    bool is_typedarray;
    NAPI_CALL(env, napi_is_typedarray(env, input_array, &is_typedarray));

    NAPI_ASSERT(env, is_typedarray, "Wrong type of arguments. Expects typed array as first argument");

    napi_valuetype valuetype1;
    NAPI_CALL(env, napi_typeof(env, args[1], &valuetype1));

    NAPI_ASSERT(env, valuetype1 == napi_number, "Wrong type of arguments. Expects number as second argument");

    int nClusters;
    NAPI_CALL(env, napi_get_value_int32(env, args[1], &nClusters));

    napi_typedarray_type type;
    napi_value input_buffer;
    size_t byte_offset;
    size_t length;
    NAPI_CALL(env, napi_get_typedarray_info(
        env, input_array, &type, &length, NULL, &input_buffer, &byte_offset));

    void* data;
    size_t byte_length;
    NAPI_CALL(env, napi_get_arraybuffer_info(
        env, input_buffer, &data, &byte_length));

    NAPI_ASSERT(env, type == napi_float64_array, "Wrong type of arguments. Expects float typed array");

    // TODO check that nClusters < size
    napi_value output_buffer;
    void * output_ptr = NULL;
    NAPI_CALL(env, napi_create_arraybuffer(env, byte_length, &output_ptr, &output_buffer));

    napi_value output_array;
    NAPI_CALL(env, napi_create_typedarray(
        env, napi_float64_array, nClusters, output_buffer, byte_offset, &output_array));

    double* input_doubles = (double*)((uint8_t*)(data) + byte_offset);
    double* output = (double*)(output_ptr);

    ckmeans(input_doubles, length, output, nClusters);
    return output_array;
}

napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor descriptors[] = {
        DECLARE_NAPI_PROPERTY("ckmeans", MyFunction),
      };

      NAPI_CALL(env, napi_define_properties(
          env, exports, sizeof(descriptors) / sizeof(*descriptors), descriptors));
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)