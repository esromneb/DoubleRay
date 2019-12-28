// #include <stdio.h>
#include <iostream>
#include <stdint.h>


using namespace std;

#include "vec3.h"



void t1(void) {
    vec3 v1(1,2,3);

    cout << v1.str() << "\n";
}

int main(int argc, char ** argv) {
    // printf("Hello Precilla\n");
    t1();
    cout << "Hello Precilla\n";
}



extern "C" {

uint32_t get4(void) {
    return 4;
}

}

