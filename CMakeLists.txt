cmake_minimum_required(VERSION 3.16)
project(wasm_tint_wgsl_reflect)
# set project limits
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
if(EMSCRIPTEN)
    # When you use SIDE_MODULE you are opting int emscripten's dynamic linking system, 
    # which means you need to build a MAIN_MODULE and use the emscripten-generated js file 
    # for the that main module to then load the side module.
    # If you just want to build a standalone wasm module and don't want use emscripten generated JS then the option you probably want is -sSTANDALONE_WASM (However in this you don't even need that since it is the default setting when build to and output file with the .wasm extension). See https://v8.dev/blog/emscripten-standalone-wasm for more
    # https://stackoverflow.com/questions/65946529/emscripten-webassembly-exporting-class-import-13-module-got-func-error-mod
    # compiler Settings: https://emscripten.org/docs/tools_reference/settings_reference.html
    # https://github.com/emscripten-core/emscripten/issues/6351
    # v8 blog https://v8.dev/blog/emscripten-standalone-wasm
    set(DAWN_FETCH_DEPENDENCIES ON)
    set(TINT_BUILD_WGSL_READER ON)
    set(TINT_BUILD_WGSL_WRITER OFF)
    set(TINT_BUILD_SPV_READER OFF)
    set(TINT_BUILD_SPV_WRITER OFF)
    set(TINT_BUILD_HLSL_WRITER OFF)
    set(TINT_BUILD_MSL_WRITER OFF)
    set(TINT_BUILD_GLSL_WRITER OFF)
    set(TINT_BUILD_IR OFF)
    set(TINT_BUILD_CMD_TOOLS OFF)
    set(TINT_DOCS_WARN_AS_ERROR OFF)
    set(TINT_BUILD_SYNTAX_TREE_WRITER OFF)
    set(TINT_BUILD_FUZZERS OFF)
    set(TINT_BUILD_SPIRV_TOOLS_FUZZER OFF)
    set(TINT_BUILD_AST_FUZZER OFF)
    set(TINT_BUILD_REGEX_FUZZER OFF)
    set(TINT_BUILD_BENCHMARKS OFF)
    set(TINT_BUILD_TESTS OFF)
    set(TINT_BUILD_AS_OTHER_OS OFF)
    set(TINT_BUILD_REMOTE_COMPILE OFF)
    set(TINT_ENABLE_MSAN OFF)
    set(TINT_ENABLE_ASAN OFF)
    set(TINT_ENABLE_UBSAN OFF)
    set(TINT_WERROR OFF)
    set(TINT_ENABLE_BREAK_IN_DEBUGGER OFF)
    set(TINT_EMIT_COVERAGE OFF)
    set(TINT_CHECK_CHROMIUM_STYLE OFF)
    set(TINT_SYMBOL_STORE_DEBUG_NAME OFF)
    set(EMCC_DEBUG 1)
    set(SOURCES 
        "src/warp.cc" 
        "src/uniform_reflect.h" 
        "src/uniform_reflect.cc"
    )
    add_subdirectory(third_party/tint EXCLUDE_FROM_ALL)
    add_executable(wtwr ${SOURCES})
    # set_target_properties(wtwr PROPERTIES SUFFIX ".html")
    set_target_properties(wtwr PROPERTIES SUFFIX ".wasm")
    target_compile_options(wtwr
        PUBLIC
        -Os # -Oz
        -fPIC
        -flto
        -sSIDE_MODULE=1
    )
    target_link_options(wtwr 
        PRIVATE
        -sEXPORT_ALL=1
        -sSIDE_MODULE=1
        -sWASM_BIGINT
        -sWASM=1
        -sSTANDALONE_WASM
        -sALLOW_MEMORY_GROWTH=1
        -sERROR_ON_UNDEFINED_SYMBOLS=1
        --no-entry
        --profiling-funcs
    )
    # set_target_properties(wtwr PROPERTIES COMPILE_FLAGS "--no-entry")
    # set_target_properties(wtwr PROPERTIES COMPILE_FLAGS "-Oz")
    # set_target_properties(wtwr PROPERTIES COMPILE_FLAGS "-flto") 
    # set_target_properties(wtwr PROPERTIES COMPILE_FLAGS "--profiling-funcs")
    # set_target_properties(wtwr PROPERTIES COMPILE_FLAGS "-s SIDE_MODULE=1") 
    # set_target_properties(wtwr PROPERTIES COMPILE_FLAGS "-s WASM_BIGINT") 
    # set_target_properties(wtwr PROPERTIES COMPILE_FLAGS "-s WASM=1") 
    # set_target_properties(wtwr PROPERTIES COMPILE_FLAGS "-s STANDALONE_WASM") 
    # set_target_properties(wtwr PROPERTIES LINK_FLAGS "-s ERROR_ON_UNDEFINED_SYMBOLS=0")
    # set_target_properties(wtwr PROPERTIES LINK_FLAGS "-s ALLOW_MEMORY_GROWTH=1") 
    # set_target_properties(wtwr PROPERTIES LINK_FLAGS "-Oz --profiling-funcs -s STANDALONE_WASM -s WASM_BIGINT -s ERROR_ON_UNDEFINED_SYMBOLS=0 --no-entry --minify=0")
    # set_target_properties(wtwr PROPERTIES LINK_FLAGS    "-Os -s FETCH_DEBUG=1 -s WASM=1 -s SIDE_MODULE=1 -s STANDALONE_WASM --no-entry")
    # set_target_properties(wtwr PROPERTIES COMPILE_FLAGS "-Os -s SIDE_MODULE=1 ")
    # set_target_properties(wtwr PROPERTIES LINK_FLAGS "-Os -s WASM=1 -s SIDE_MODULE=1 -s STANDALONE_WASM --no-entry")
    # set_target_properties(wtwr PROPERTIES LINK_FLAGS "-Os -s WASM=1 -s STANDALONE_WASM --no-entry")
    # target_link_libraries(wtwr PRIVATE tint_lang_wgsl_reader)
    # target_link_options(wtwr PRIVATE -03)
    # target_link_options(wtwr PRIVATE -sEXPORTED_FUNCTIONS=["_wasm_tint_wgsl_reflect_valid"])
    # target_link_options(wtwr PRIVATE -sSTANDALONE_WASM)
    # target_link_options(wtwr PRIVATE -sNO_ENTRY)
    
else()
    message("[ERROR] only support 'EMSCRIPTEN' env, please use 'emcmake cmake xx' build wtwr.")
endif()
