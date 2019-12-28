#include <stdio.h>
#include <stdint.h>

int main(int argc, char ** argv) {
    printf("Hello Precilla\n");
}

extern "C" {

uint32_t get4(void) {
    return 4;
}

}
