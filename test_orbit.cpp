#include "Vec.hpp"

#include <iostream>

using namespace std;

int main(void) {
    cout << "foo\n";


    Vec c(4);

    c.data[0] = 0;
    c.data[1] = 1;
    c.data[2] = -2;
    c.data[3] = 0;

    // c.rot_x(0.4);
}
