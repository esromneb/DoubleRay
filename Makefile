
.PHONY: all

all: out/ray.wasm




CPP_FILES = \
main2.cpp \
vec3.cpp


out/ray.wasm: $(CPP_FILES)
	emcc $(CPP_FILES) -s WASM=1 -o out/ray.html \
	-s EXPORTED_FUNCTIONS='["_get4", "_main"]' \
	-s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]'


