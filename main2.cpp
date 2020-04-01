// #include <stdio.h>

#include "Vec3.hpp"
#include "Vec.hpp"
#include "RayEngine.hpp"
#include "fileio.h"
#include "Parser.hpp"
#include "RayApi.hpp"


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



RayEngine* engine;
std::vector<std::vector<uint32_t>> buffer;
float gain = 1.1;

void t1(void) {
    Vec3 v1(1,2,3);

    cout << v1.str() << "\n";

    // cout << v1.str() << "\n";
}

extern "C" {

void setupEngine(void) {
    engine = new RayEngine();
    engine->resize(400);

    setRayApiTarget(engine);

    // engine->makeObjects();
    // engine->render();

    uint32_t x = 400;
    uint32_t y = 400;
    buffer.resize(x);
    for(auto &row : buffer) {
        row.resize(y);
    }

    engine->makeObjects();

    // readWaveFront( *engine );

}




} // extern C

#ifdef NOTUSEDFORNOW
void copyBuffer(void) {
    uint32_t px = 400;

    float rmax = 0;

    auto scale = RayEngine::scale;

    // glBegin(GL_POINTS);
    for( int y = 0; y < px; y++ ) {
        for( int x = 0; x < px; x++ ) {
            float r = engine->r[x+y*px];
            float g = engine->g[x+y*px];
            float b = engine->b[x+y*px];
            float rs = gain + (r / scale);
            float gs = gain + (g / scale);
            float bs = gain + (b / scale);

            uint8_t rb = (rs > 0) ? ( (rs>=255) ? 255 : rs ) : (0);
            uint8_t gb = (gs > 0) ? ( (gs>=255) ? 255 : gs ) : (0);
            uint8_t bb = (bs > 0) ? ( (bs>=255) ? 255 : bs ) : (0);


            buffer[x][px-y] = (rb<<16) | (gb<<8) | bb;
            // buffer[x][y] = rb;
            // cout << r << "\n";
            // if( r > rmax ) {
            //     rmax = r;
            // }
            // glColor3f( r[x+y*px], g[x+y*px], b[x+y*px] );
            // glVertex2i( x, y );
        }
    }

    // cout << rmax << "\n";   
    // glEnd();
}




void printBuffer(void) {
    uint32_t px = 400;

    float rmax = 0;


    // glBegin(GL_POINTS);
    for( int y = 0; y < px; y++ ) {
        for( int x = 0; x < px; x++ ) {
            float r = engine->r[x+y*px];
            float g = engine->g[x+y*px];
            float b = engine->b[x+y*px];
            

            cout << r << "\n";

            // buffer[x][y] = rb;
            // cout << r << "\n";
            // if( r > rmax ) {
            //     rmax = r;
            // }
            // glColor3f( r[x+y*px], g[x+y*px], b[x+y*px] );
            // glVertex2i( x, y );
        }
    }

    // cout << rmax << "\n";   
    // glEnd();
}



void fakeBuffer(void) {
    uint32_t px = 400;

    // uint32_t m = 25

    for( int x = 0; x < px; x++ ) { // x
        for( int y = 0; y < px; y++ ) { // y

            uint8_t rb = 255;
            if( y < 255 ) {
                rb = y;
            }

            uint8_t gb = 200;
            if( x < 255 ) {
                gb = 255-x;
            }

            uint8_t bb = 0;

            if( y > 100 && y < 300 ) {
                bb = 240;
            }

            buffer[x][y] = (rb<<16) | (gb<<8) | bb;

        }
    }
}

int main3(int argc, char ** argv) {
    // printf("Hello Precilla\n");
    cout << "Enter main()" << "\n";
    // t1();
    setupEngine();
    render();
    copyBuffer();
    // printBuffer();
    // fakeBuffer();
    // cout << "Hello Precilla\n";
    return 0;
}
#endif

SDL_Surface *screen = 0;

std::chrono::steady_clock::time_point frames_then;
unsigned frames = 0;
unsigned frames_p = 0;


// unsigned frame_sleep = 0;


void officialRenderRainbow(bool boolA, bool boolB) {
    if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);
      for (int i = 0; i < 400; i++) {
        for (int j = 0; j < 400; j++) {

// #ifdef TEST_SDL_LOCK_OPTS
          // Alpha behaves like in the browser, so write proper opaque pixels.
          const uint8_t alpha = 255;
// #else
//           // To emulate native behavior with blitting to screen, alpha component is ignored. Test that it is so by outputting
//           // data (and testing that it does get discarded)
          // int alpha = (i+j) % 255;
// #endif

          const uint8_t r = boolA ? (255-i) : i;
          const uint8_t g = boolB ? (255-j) : j;
          const uint8_t b = 255-i;


          *((Uint32*)screen->pixels + i * 400 + j) = SDL_MapRGBA(screen->format, r, g, b, alpha);
        }
      }
      if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
      SDL_Flip(screen);
      frames++;
      // usleep(10E3);

      if( (frames & (0xfff>>1)) == 0 ) {
        unsigned delta = frames - frames_p;
        auto frames_now = std::chrono::steady_clock::now();

        const size_t elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>( 
            frames_now - frames_then
        ).count();

        double elapsed_s = elapsed_us / 1E6;
        double fps = delta / elapsed_s;

        // cout << "Frames: " << frames << "\n";
        cout << "FPS: " << fps << "\n";

        frames_then = frames_now;
        frames_p = frames;
      }

      // usleep(frame_sleep);
}


void officialCopyBuffer(void) {
    const uint32_t px = 400;

    auto scale = RayEngine::scale;

    // float rmax = 0;

    if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);

    // glBegin(GL_POINTS);
    for( int y = 0; y < px; y++ ) {
        for( int x = 0; x < px; x++ ) {
            float r = engine->r[x+y*px];
            float g = engine->g[x+y*px];
            float b = engine->b[x+y*px];
            float rs = gain + (r / scale);
            float gs = gain + (g / scale);
            float bs = gain + (b / scale);

            uint8_t rb = (rs > 0) ? ( (rs>=255) ? 255 : rs ) : (0);
            uint8_t gb = (gs > 0) ? ( (gs>=255) ? 255 : gs ) : (0);
            uint8_t bb = (bs > 0) ? ( (bs>=255) ? 255 : bs ) : (0);


            // buffer[x][px-y] = (rb<<16) | (gb<<8) | bb;

            *((Uint32*)screen->pixels + ((px-1-y) * px) + x) = SDL_MapRGBA(screen->format, rb, gb, bb, 255);


            // buffer[x][y] = rb;
            // cout << r << "\n";
            // if( r > rmax ) {
            //     rmax = r;
            // }
            // glColor3f( r[x+y*px], g[x+y*px], b[x+y*px] );
            // glVertex2i( x, y );
        }
    }

    if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);
    SDL_Flip(screen);

    // cout << rmax << "\n";
    // glEnd();
}



// sets global screen
void initSetResolution(const unsigned x, const unsigned y) {
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(x, y, 32, SDL_SWSURFACE);

    #ifdef TEST_SDL_LOCK_OPTS
    EM_ASM("SDL.defaults.copyOnLock = false; SDL.defaults.discardOnLock = true; SDL.defaults.opaqueFrontBuffer = false;");
    #endif

}

int main(int argc, char ** argv) {

    // initSetResolution(256, 256);
    initSetResolution(400, 400);
    
    frames_then = std::chrono::steady_clock::now();


    officialRenderRainbow(false, false);

    // SDL_Quit();

    return 0;
}

static uint32_t nextVal = 0;




///
/// These are all of the C++ -> Javascript
///

EM_JS(void, call_alert, (), {
  alert('hello world!');
  // throw 'all done';
});






///
/// These are all of the Javascript -> C++ functions
///

extern "C" {

void renderNextRainbow(void) {
    static int v = 1;
    switch(v) {
        default:
        case 0:
            officialRenderRainbow(false, false);
            v = 1;
            break;
        case 1:
            officialRenderRainbow(false, true);
            v = 2;
            break;
        case 2:
            officialRenderRainbow(true, false);
            v = 3;
            break;
        case 3:
            officialRenderRainbow(true, true);
            v = 0;
            break;
    }
}



void doRenderOfficial(void) {
    // return 4;
    render();
    // cout << "Render finished\n";
    officialCopyBuffer();
    // cout << "Copy finished\n";
}



} // extern C





