
.PHONY: all clean e

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

# this is a list of all C functions we want to publish to javascript
# In the main cpp file, each of these is wrapped in extern "C" {}
# the version here has a prepended underscore
# all lines must have trailing comma
EXPORT_STRING = \
"_get4", \
"_getNext", \
"_getPixel", \
"_doRender", \
"_doDebugRender", \
"_setupEngine", \
"_debug2", \
"_setFrameSleep", \
"_onRuntimeInitialized", \
"_onCustomMessage", \
"_renderNextRainbow", \
"_coutInt", \
"_coutIntDual", \
"_doRenderOfficial", \
"_setCamera", \
"_setScale",

TEMPLATE_FILE = template/proxy_controls.html
JS_TEMPLATE_FILE = template/pre.ray.js



out/ray.wasm: $(CPP_FILES) $(HPP_FILES) $(TEMPLATE_FILE) $(JS_TEMPLATE_FILE) Makefile
	emcc $(CPP_FILES) -s WASM=1 -o out/ray.html \
	--shell-file $(TEMPLATE_FILE) \
	--proxy-to-worker \
	--pre-js $(JS_TEMPLATE_FILE) \
	-s EXPORTED_FUNCTIONS='[$(EXPORT_STRING) "_main"]' \
	-s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
	'-std=c++2a'


e: out/empty

out/empty:  $(TEMPLATE_FILE) $(JS_TEMPLATE_FILE) Makefile
	emcc Empty.cpp -s WASM=1 -o out/ray.html \
	--shell-file $(TEMPLATE_FILE) \
	--proxy-to-worker \
	--pre-js $(JS_TEMPLATE_FILE) \
	-s EXPORTED_FUNCTIONS='["_main"]' \
	-s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
	'-std=c++2a'
	touch main2.cpp # force make to run again if "make all" is run next



# '-Wshadow-all'
#--proxy-to-worker \
#-s PROXY_TO_WORKER_FILENAME='custom.ray' \

# not working due to chrome not liking these options
#-s USE_PTHREADS=1 -s RESERVED_FUNCTION_POINTERS=1
#-s PTHREAD_POOL_SIZE=4

.PHONY: copy_files_target copy

copy: copy_files_target



# I forget how to copy file and do the sensativity list thing correctly
# so for now this needs to be manual

COPY_LIST = \
template/jquery-3.4.1.min.js \
template/pre.ray.js

copy_files_target:
	cp $(COPY_LIST) out/


clean:
	rm -rf out/ray.wasm out/ray.js out/ray.html
