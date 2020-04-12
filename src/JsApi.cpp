#include "JsApi.hpp"

#include <iostream>
#include <vector>
#include <stdint.h>
#include <chrono>
#include <unistd.h> //usleep
#include <functional>
#include <cmath>


#include <stdio.h>
#include <SDL/SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif



using namespace std;


///
/// These are all of the C++ -> Javascript
///


EM_JS(void, postB64, (const char* v), {
    postB64ToMain(v);
});


EM_JS(void, postFixed, (), {
    postToMain(0, "hello message0");
    postToMain(1, "hello message1");
    // alert('hello world!');
    // throw 'all done';
});

