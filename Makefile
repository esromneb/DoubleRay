
.PHONY: all

all: wasm




CPP_FILES = \
main2.cpp \
vec3.cpp


wasm:
	emcc $(CPP_FILES) -s WASM=1 -o hello.html \
	-s EXPORTED_FUNCTIONS='["_get4", "_main"]' \
	-s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]'