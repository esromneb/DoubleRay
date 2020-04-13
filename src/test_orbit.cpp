#include "Vec.hpp"

#include <iostream>
#include <cmath>

using namespace std;

int main(void) {
    cout << "foo\n";


    Vec c(4);

    c.data[0] = 0;
    c.data[1] = 1;
    c.data[2] = -2;
    c.data[3] = 0;


    if( false ) {

        cout << "Before:\n" << c.str(true) << "\n";

        c.rot_y(0.05);

        cout << "After:\n" << c.str(true) << "\n";
    }

    unsigned frames = 5;

    float bump = 2*M_PI / frames;

    cout << M_PI << "\n\n";
    
    cout << c.str() << "\n";

    for(unsigned i = 0; i < frames; i++) {
        c.rot_y(bump);
        cout << c.str() << "\n";
    }


    // c.rot_x(0.4);
}

