
.PHONY: all clean

all: out/ray.wasm



HPP_FILES = \
raytrace.h \
vec3.h

CPP_FILES = \
main2.cpp \
vec3.cpp \
raytrace.cpp

EXPORT_STRING = \
"_get4", \
"_getNext", \
"_getPixel", \
"_doRender", \
"_doDebugRender", \
"_setScale",



out/ray.wasm: $(CPP_FILES) $(HPP_FILES)
	emcc $(CPP_FILES) -s WASM=1 -o out/ray.html \
	-s EXPORTED_FUNCTIONS='[$(EXPORT_STRING) "_main"]' \
	-s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
	'-std=c++2a'


clean:
	rm -rf out/ray.wasm out/ray.js out/ray.html
