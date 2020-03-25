
.PHONY: all clean

all: out/ray.wasm



HPP_FILES = \
RayEngine.hpp \
Vec3.hpp \
Poly.hpp

CPP_FILES = \
main2.cpp \
Vec3.cpp \
Poly.cpp \
RayEngine.cpp

EXPORT_STRING = \
"_get4", \
"_getNext", \
"_getPixel", \
"_doRender", \
"_doDebugRender", \
"_setScale",



out/ray.wasm: $(CPP_FILES) $(HPP_FILES) Makefile
	emcc $(CPP_FILES) -s WASM=1 -o out/ray.html \
	-s EXPORTED_FUNCTIONS='[$(EXPORT_STRING) "_main"]' \
	-s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
	'-std=c++2a'

# not working due to chrome not liking these options
#-s USE_PTHREADS=1 -s RESERVED_FUNCTION_POINTERS=1
#-s PTHREAD_POOL_SIZE=4


clean:
	rm -rf out/ray.wasm out/ray.js out/ray.html
