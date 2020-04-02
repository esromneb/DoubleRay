
.PHONY: all clean e

all: out/ray.wasm



HPP_FILES = \
RayEngine.hpp \
Vec3.hpp \
Poly.hpp \
Matrix.hpp \
fileio.h \
Material.hpp \
Ray.hpp \
Parser.hpp \
RayApi.hpp \
json.hpp \
Macros.hpp \
Vec.hpp

WASM_MAIN = main2.cpp

CPP_FILES = \
Vec3.cpp \
Poly.cpp \
Matrix.cpp \
RayEngine.cpp \
fileio.cpp \
Material.cpp \
Ray.cpp \
Parser.cpp \
RayApi.cpp \
Vec.cpp

# this is a list of all C functions we want to publish to javascript
# In the main cpp file, each of these is wrapped in extern "C" {}
# the version here has a prepended underscore
# all lines must have trailing comma
EXPORT_STRING = \
"_setupEngine", \
"_onRuntimeInitialized", \
"_onCustomMessage", \
"_renderNextRainbow", \
"_coutInt", \
"_coutIntDual", \
"_doRenderOfficial", \
"_setCamera", \
"_setDepth", \
"_setAmbientColor", \
"_setGlobalC", \
"_setSphere", \
"_setSphereCount", \
"_setLightCount", \
"_setLight", \
"_dumpPoly", \
"_setupOrbit", \
"_nextOrbitRender", \
"_dumpCamera", \
"_chokeOutput", \
"_setPrint", \
"_setNoHitColor", \
"_setHighlightPixel", \
"_parseJsonScene", \
"_parseJsonSceneFragment", \
"_setScale",

TEMPLATE_FILE = template/proxy_controls.html
JS_TEMPLATE_FILE = template/pre.ray.js

# warning and error flags
CLANG_WARN_FLAGS = \
-Wall -Wextra \
-Wno-ignored-qualifiers \
-Wundef \
-Werror=return-type
# -Wshadow
#  -Wconversion

# works however adds 100ms or more to the
# render time
#-s DISABLE_EXCEPTION_CATCHING=0 \

out/ray.wasm: $(WASM_MAIN) $(CPP_FILES) $(HPP_FILES) $(TEMPLATE_FILE) $(JS_TEMPLATE_FILE) Makefile
	emcc $(WASM_MAIN) $(CPP_FILES) -s WASM=1 -o out/ray.html \
	--shell-file $(TEMPLATE_FILE) \
	--proxy-to-worker \
	--pre-js $(JS_TEMPLATE_FILE) \
	--preload-file 'root_fs' \
	-s EXPORTED_FUNCTIONS='[$(EXPORT_STRING) "_main"]' \
	-s EXTRA_EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
	'-std=c++2a' '-O2'


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

.PHONY: copy_files_target copy copy_fs

copy: copy_files_target copy_fs



# I forget how to copy file and do the sensativity list thing correctly
# so for now this needs to be manual

COPY_LIST = \
template/jquery-3.4.1.min.js \
template/LoadSave.js \
template/GIFEncoder.js \
template/LZWEncoder.js \
template/NeuQuant.js \
template/b64.js

# copy files required to compile the project (js etc)
copy_files_target:
	cp $(COPY_LIST) out/



FS_COPY_LIST = \
models/scene2.txt \
models/unit_cube.txt \
models/scenep5.txt \
models/1tri.txt \
models/1triB.txt

# copy files which will act as the root filesystem
copy_fs:
	mkdir -p root_fs
	cp $(FS_COPY_LIST) root_fs/


# files need only for test or desktop builds (aka not WASM builds)

HPP_TEST_FILES = \
lodepng.h \
HandlePng.hpp

CPP_TEST_FILES = \
lodepng.cpp \
HandlePng.cpp



test_orbit2: test_orbit.cpp $(CPP_FILES) $(HPP_FILES) Makefile
	g++ test_orbit.cpp $(CPP_FILES) -o $@

test_parse2: test_parse.cpp $(CPP_FILES) $(HPP_FILES) Makefile
	g++ $< $(CPP_FILES) -std=c++17  -g -o $@


# $< name of first prerequisite
# $@ name of target
test_orbit: test_orbit.cpp $(CPP_FILES) $(HPP_FILES) Makefile
	clang++ $(CLANG_WARN_FLAGS) -std=c++2a $< $(CPP_FILES) -g -o $@

test_vec: test_vec.cpp $(CPP_FILES) $(HPP_FILES) Makefile
	clang++ $(CLANG_WARN_FLAGS) -std=c++2a $< $(CPP_FILES) -g -o $@


test_refl: test_refl.cpp $(CPP_FILES) $(HPP_FILES) Makefile
	clang++ $(CLANG_WARN_FLAGS) -std=c++2a $< $(CPP_FILES) -g -o $@


test_parse: test_parse.cpp $(CPP_FILES) $(HPP_FILES) Makefile
	clang++ $(CLANG_WARN_FLAGS) -std=c++2a $< $(CPP_FILES) -g -o $@

test_png: test_png.cpp $(CPP_FILES) $(HPP_FILES) $(HPP_TEST_FILES) Makefile
	clang++ $(CLANG_WARN_FLAGS) -std=c++2a $< $(CPP_FILES) $(CPP_TEST_FILES) -g -o $@


.PHONY: rmtest movetestideal rmideal

rmtest: 
	rm -rf img/test/*.png

rmideal: 
	rm -rf img/ideal/*.png

movetestideal: rmideal
	mv img/test/*.png img/ideal/


clean:
	rm -rf out/ray.wasm out/ray.js out/ray.html out/ray.data
