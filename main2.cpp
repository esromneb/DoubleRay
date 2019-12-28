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

void t1(void) {
    vec3 v1(1,2,3);

    cout << v1.str() << "\n";

    // cout << v1.str() << "\n";
}

void setupEngine(void) {
    engine = new rayEngine;
    uint32_t x = 400;
    uint32_t y = 400;
    buffer.resize(x);
    for(auto &row : buffer) {
        row.resize(y);
    }
}


void render(void) {
    renderDone = false;
    engine->render();
    renderDone = true;
}

void copyBuffer(void) {
    uint32_t px = 400;

    // glBegin(GL_POINTS);
    for( int j = 0; j < px; j++ ) {
        for( int i = 0; i < px; i++ ) {
            cout << engine->r[i+j*px];
            // glColor3f( r[i+j*px], g[i+j*px], b[i+j*px] );
            // glVertex2i( i, j );
        }
    }
    // glEnd();

}

int main(int argc, char ** argv) {
    // printf("Hello Precilla\n");
    t1();
    setupEngine();
    render();
    copyBuffer();
    cout << "Hello Precilla\n";
}

uint32_t nextVal = 0;


extern "C" {

uint32_t get4(void) {
    return 4;
}

uint32_t getNext(void) {
    return nextVal++;
}

uint32_t getPixel(const uint32_t x, const uint32_t y) {
    return x+y;
}



}

