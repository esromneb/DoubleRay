
.PHONY: all

all: out/ray.wasm



HPP_FILES = \
raytrace.h \
vec3.h

CPP_FILES = \
main2.cpp \
vec3.cpp \
raytrace.cpp


out/ray.wasm: $(CPP_FILES) $(HPP_FILES)
	emcc $(CPP_FILES) -s WASM=1 -o out/ray.html \
	-s EXPORTED_FUNCTIONS='["_get4", "_main"]' \
	-s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]'


