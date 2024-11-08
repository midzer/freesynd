# Emscripten

## Build

```
mkdir build
cd build
emcmake cmake .. -DCMAKE_BUILD_TYPE=Release
emmake make
```

## Link

```
em++ -flto -O3 ../../../engine/libfs_engine.a ../../../engine/libfs_engine_sdl.a ../../../engine/libfs_engine_sdlmixer.a ../../../kernel/libfs_kernel.a ../../../utils/libfs_utils.a *.o */*.o -o index.html -sUSE_SDL=2 -sUSE_SDL_MIXER=2 -sSDL2_MIXER_FORMATS='["mid"]' -sUSE_SDL_IMAGE=2 -sSDL2_IMAGE_FORMATS=png -sUSE_LIBPNG -sASYNCIFY -sSTACK_SIZE=262144 -sEXIT_RUNTIME=1 -sINITIAL_MEMORY=128mb -sENVIRONMENT=web --preload-file data/ --preload-file freesynd.ini --preload-file user.conf --preload-file dgguspat/ --preload-file timidity.cfg --closure 1 -sEXPORTED_RUNTIME_METHODS=['allocate']
```
