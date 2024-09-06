wasm tint wgsl reflect (wtwr) lib

> [emscripten_with_cmake](https://stunlock.gg/posts/emscripten_with_cmake/)
```shell
```

> add submodule / dependencies
```shell
git submodule add -b main https://dawn.googlesource.com/tint third_party/tint
```
# build
> init 
- init submodule
```shell
git submodule update --init --recursive
```
> check tint branch
```shell
cd third_party/tint
git branch
// git checkout main
// git pull
```
> emscripten make project
```shell
emcmake /Applications/CMake331.app/Contents/bin/cmake -B build -S.
/Applications/CMake331.app/Contents/bin/cmake --build build -j8 
```
> default cmake
```shell
emcmake cmake -B build -S.
cmake --build build
```

