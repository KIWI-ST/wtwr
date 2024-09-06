/**
 * https://github.com/BabylonJS/twgsl/blob/main/Core/twgsl/Source/main.cpp
 */

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#else
#define EMSCRIPTEN_KEEPALIVE
#endif

#include <iostream>
#include "uniform_reflect.h"

extern "C"
{
    EMSCRIPTEN_KEEPALIVE int add(int a, int b)
    {
        return a + b;
    }

    EMSCRIPTEN_KEEPALIVE int sub(int a, int b)
    {
        return a - b;
    }

    EMSCRIPTEN_KEEPALIVE void tint_wgsl_reflect_valid()
    {
        wasm_tint_wgsl_reflect_valid();
    }
}
