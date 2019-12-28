// #include <stdio.h>
#include <iostream>
#include <vector>
#include <stdint.h>



using namespace std;

#include "vec3.h"
#include "raytrace.h"


rayEngine* engine;
bool renderDone = false;
std::vector<std::vector<uint32_t>> buffer;
float scale = 0.004;
float gain = 1.1;

void t1(void) {
    vec3 v1(1,2,3);

    cout << v1.str() << "\n";

    // cout << v1.str() << "\n";
}

void setupEngine(void) {
    engine = new rayEngine();
    engine->resize(400);
    engine->makeObjects();


    // engine->makeObjects();
    // engine->render();

    uint32_t x = 400;
    uint32_t y = 400;
    buffer.resize(x);
    for(auto &row : buffer) {
        row.resize(y);
    }
}

extern "C" {

void render(void) {
    renderDone = false;
    engine->render();
    renderDone = true;
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


            buffer[x][y] = (rb<<16) | (gb<<8) | bb;
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

int main(int argc, char ** argv) {
    // printf("Hello Precilla\n");
    // t1();
    setupEngine();
    render();
    copyBuffer();
    // printBuffer();
    // fakeBuffer();
    cout << "Hello Precilla\n";
}

uint32_t nextVal = 0;


extern "C" {

void doRender(void) {
    // return 4;
    render();
    copyBuffer();
    cout << "Render finished\n";
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



}

