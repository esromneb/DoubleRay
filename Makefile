
.PHONY: all clean

all: out/ray.wasm



HPP_FILES = \
RayEngine.hpp \
Vec3.hpp \
Poly.hpp \
Matrix.hpp

CPP_FILES = \
main2.cpp \
Vec3.cpp \
Poly.cpp \
Matrix.cpp \
RayEngine.cpp 

# all lines must have trailing comma
EXPORT_STRING = \
"_get4", \
"_getNext", \
"_getPixel", \
"_doRender", \
"_doDebugRender", \
"_debug2", \
"_setScale",

TEMPLATE_FILE = template/controls.html



out/ray.wasm: $(CPP_FILES) $(HPP_FILES) $(TEMPLATE_FILE) Makefile
	emcc $(CPP_FILES) -s WASM=1 -o out/ray.html \
	--shell-file $(TEMPLATE_FILE) \
	-s EXPORTED_FUNCTIONS='[$(EXPORT_STRING) "_main"]' \
	-s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
	'-std=c++2a'

# '-Wshadow-all'

# not working due to chrome not liking these options
#-s USE_PTHREADS=1 -s RESERVED_FUNCTION_POINTERS=1
#-s PTHREAD_POOL_SIZE=4


clean:
	rm -rf out/ray.wasm out/ray.js out/ray.html
