// #include <stdio.h>

#include "Vec3.hpp"
#include "Vec.hpp"
#include "RayEngine.hpp"
#include "fileio.h"


#include <iostream>
#include <vector>
#include <stdint.h>
#include <chrono>
#include <unistd.h> //usleep
#include <functional> //usleep
#include <cmath>


#include <stdio.h>
#include <SDL/SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif



using namespace std;



RayEngine* engine;
bool renderDone = false;
std::vector<std::vector<uint32_t>> buffer;
float scale = 0.006;
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


void render(void) {
    renderDone = false;

    const auto start = std::chrono::steady_clock::now();
    engine->render();
    const auto end = std::chrono::steady_clock::now();

    renderDone = true;

    if( true ) {
        const size_t elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>( 
            end - start
        ).count();
        const double elapsed_ms = elapsed_us / 1000.0;
        cout << "Render took " << elapsed_ms << "ms" << "\n";
    }
}

}

void copyBuffer(void) {
    uint32_t px = 400;

    float rmax = 0;


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




// ^
// |
// |
// y
// x---->
//

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

SDL_Surface *screen = 0;

std::chrono::steady_clock::time_point frames_then;
unsigned frames = 0;
unsigned frames_p = 0;


unsigned frame_sleep = 0;


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

      usleep(frame_sleep);
}


void officialCopyBuffer(void) {
    const uint32_t px = 400;

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

    // while(1) {
    //     officialRenderRainbow(false, false);
    //     officialRenderRainbow(false, true);
    //     officialRenderRainbow(true, false);
    //     officialRenderRainbow(true, true);
    // }

      // printf("you should see a smoothly-colored square - no sharp lines but the square borders!\n");
      // printf("and here is some text that should be HTML-friendly: amp: |&| double-quote: |\"| quote: |'| less-than, greater-than, html-like tags: |<cheez></cheez>|\nanother line.\n");

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



// automatically resize the vector
// (grow only)
template<class T>
void growOnly(const int index, T& vec) {
    if( (index + 1) > vec.size() ) {
        vec.resize((index+1));
    }
}




///
/// These are all of the Javascript -> C++ functions
///

extern "C" {

void doRender(void) {
    // return 4;
    render();
    copyBuffer();
    cout << "Render finished\n";
}

void doRenderOfficial(void) {
    // return 4;
    render();
    cout << "Render finished\n";
    officialCopyBuffer();
    cout << "Copy finished\n";
}


void doDebugRender(void) {
    // return 4;
    fakeBuffer();
}

uint32_t get4(void) {
    return 4;
}

uint32_t getNext(void) {
    return nextVal++;
}

uint32_t getPixel(const uint32_t x, const uint32_t y) {
    return buffer[x][y];
}

void setScale(const float s) {
    scale = s;
}

void debug2(void) {
    // cout << "start debug2" << "\n";
    // usleep(2E6);
    // cout << "exit debug2" << "\n";

    // officialRenderRainbow(true, true);

    while(1) {
        officialRenderRainbow(false, false);
        officialRenderRainbow(false, true);
        officialRenderRainbow(true, false);
        officialRenderRainbow(true, true);
    }
}

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


void setFrameSleep(const int s) {
    frame_sleep = s;
}

void onRuntimeInitialized(void) {
    cout << "onRuntimeInitialized()" << "\n";
}

void onCustomMessage(void) {
    cout << "onCustomMessage()" << "\n";
}

void coutInt(const int a) {
    cout << "C++ got this int: " << a << "\n";

    // // float fly_0;
    // ARG_VEC3_SIG(fly);

    // fly_0 = 42;

    // cout << "fly " << fly_0 << "\n";

}

void coutIntDual(const int a, const int b) {
    cout << "C++ got these ints: " << a << ", " << b << "\n";
}

void setCamera(VEC3_ARG(location), VEC3_ARG(direction), VEC3_ARG(rotation)) {
    // cout << "Rot: " << rotation_0 << "," << rotation_1 << "," << rotation_2 << "\n";

    auto &camera = engine->camera;

    camera.o = VEC3_ARG_CTONS(location);

    camera.d = VEC3_ARG_CTONS(direction);
    camera.d.normalize();
    
    engine->up = VEC3_ARG_CTONS(rotation);
    engine->up.normalize();
}

void setDepth(const int d) {
    engine->depth = d;
}

void setAmbientColor(VEC3_ARG(color)) {
    engine->ia = VEC3_ARG_CTONS(color);
}

void setGlobalC(const int c) {
    engine->c = c;
}

void setSphereCount(const int count) {
    auto &spheres = engine->spheres;
    spheres.resize(count);
}


void setSphere(
    const int index,
    const float radius,
    VEC3_ARG(location),
    const float ambient,
    const float specular,
    const float reflected,
    const float transmitted,
    VEC3_ARG(diffuse),
    const float n
    ) {

    if(index < 0) {
        cout << "Sphere index cannot be less than 0\n";
        return;
    }

    auto &spheres = engine->spheres;

    // cout << "spheres Before size " << spheres.size() << "\n";

// index , size
    // 0 , 1
    // 1 , 2

    // automatically resize the vector
    // (grow only)
    growOnly(index, spheres);
    // if( (index + 1) > spheres.size() ) {
    //     spheres.resize((index+1));
    // }
    // cout << "spheres After size " << spheres.size() << "\n";

    spheres[index].r = radius;
    spheres[index].c = VEC3_ARG_CTONS(location);
    spheres[index].ka = ambient;
    spheres[index].ks = specular;
    spheres[index].kr = reflected;
    spheres[index].kd = VEC3_ARG_CTONS(diffuse);
    spheres[index].n = n;
    spheres[index].kt = transmitted;
}


void setLightCount(const int count) {
    auto &lights = engine->lights;
    lights.resize(count);
}

void setLight(
    const int index,
    VEC3_ARG(direction),
    VEC3_ARG(color)) {

    if(index < 0) {
        cout << "Light index cannot be less than 0\n";
        return;
    }

    auto &lights = engine->lights;

    growOnly(index, lights);

    lights[index].d = VEC3_ARG_CTONS(direction);
    lights[index].d.normalize();
    
    lights[index].color = VEC3_ARG_CTONS(color);
}

void dumpPoly(const int index) {
    const auto &poly = engine->polygons[index];

    cout << "Polygon " << index << ":\n";
    cout << "edgeCount: " << poly.edgeCount << "\n";
    cout << "tpc: " << poly.trianglePointCount << "\n";
    cout << "ka: " << poly.ka << "\n";
    cout << "kd: " << poly.kd.str() << "\n";
    cout << "ks: " << poly.ks << "\n";
    cout << "kr: " << poly.kr << "\n";
    cout << "kt: " << poly.kt << "\n";
    cout << "n : " << poly.n  << "\n";

}

typedef std::function<void(void)> scene_animation_t;

std::vector<scene_animation_t> cameraOrbit;

unsigned nextOrbitFrame = 0;


///
/// First frame is camera's current position
/// next frame is moved
/// final frame should be adjacent and animate "seamless" into the first frame
void setupOrbit(const int _frames) {
    if( _frames < 0 ) {
        cout << "Frames cannot be negative\n";
        return;
    }
    if( _frames == 0 ) {
        cout << "Frames cannot be zero\n";
        return;
    }

    const unsigned frames = (unsigned)_frames;
    cout << "Orbit frames: " << frames << "\n";

    cameraOrbit.resize(0);
    nextOrbitFrame = 0;

    const float bump = 2*M_PI / frames;

    Vec cameraOrigin(4); // make a Vec sized 4
    Vec cameraDir(4); // make a Vec sized 4

    // load the Vec3 camera into it
    cameraOrigin.data[0] = engine->camera.o[0];
    cameraOrigin.data[1] = engine->camera.o[1];
    cameraOrigin.data[2] = engine->camera.o[2];
    cameraOrigin.data[3] = 0;

    // load the Vec3 camera into it
    cameraDir.data[0] = engine->camera.d[0];
    cameraDir.data[1] = engine->camera.d[1];
    cameraDir.data[2] = engine->camera.d[2];
    cameraDir.data[3] = 0;

    // the new values for the camera's origin
    // these are lambda captured by value below
    float originX = engine->camera.o[0];
    float originY = engine->camera.o[1];
    float originZ = engine->camera.o[2];

    float dirX = engine->camera.d[0];
    float dirY = engine->camera.d[1];
    float dirZ = engine->camera.d[2];

    for(unsigned i = 0; i < frames; i++) {

        cameraOrbit.emplace_back([=](void) {
            cout << "executing frame i: " << i << "\n";
            engine->camera.o = Vec3(originX, originY, originZ);

            engine->camera.d = Vec3(dirX, dirY, dirZ);
            engine->camera.d.normalize(); // should not be needed if only rotating
        });

        if( true ) {
            cout << cameraOrigin.str() << "  " << cameraDir.str() << "\n";
        }

        // calculate next frame
        cameraOrigin.rot_z(bump);
        cameraDir.rot_z(bump);

        // load these from the Vec
        originX = cameraOrigin.data[0];
        originY = cameraOrigin.data[1];
        originZ = cameraOrigin.data[2];

        // load these from the Vec
        dirX = cameraDir.data[0];
        dirY = cameraDir.data[1];
        dirZ = cameraDir.data[2];

    }


}

void nextOrbitRender(void) {
    if( cameraOrbit.size() == 0 ) {
        cout << "nextOrbitRender() cannot run without setupOrbit() first\n";
        return;
    }

    // not sure if needed, prevent any starting glitch
    nextOrbitFrame = nextOrbitFrame % cameraOrbit.size();

    // update the scene
    cameraOrbit[nextOrbitFrame]();

    // render
    doRenderOfficial();

    nextOrbitFrame++;

    nextOrbitFrame = nextOrbitFrame % cameraOrbit.size();
}


///
///
///    "loc": [0, 1, -2],
///    "dir": [0, -0.2, 1],
///
void dumpCamera() {

    const auto& c = engine->camera;

    cout << "\"loc\": [" << c.o[0] << ", " << c.o[1] << ", " << c.o[2] << "],\n";
    cout << "\"dir\": [" << c.d[0] << ", " << c.d[1] << ", " << c.d[2] << "],\n";

    // cout << engine->camera.o.str() << "\n";
    // cout << engine->camera.d.str() << "\n";
}

void chokeOutput(int il, int ih, int jl, int jh) {
    engine->il = il;
    engine->ih = ih;
    engine->jl = jl;
    engine->jh = jh;
}

void setPrint(int p) {
    engine->print = p?true:false;
}


} // extern C





