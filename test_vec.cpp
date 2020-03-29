#include "Vec.hpp"

#include <iostream>

using namespace std;

int main(void) {
    cout << "in test vec\n";



    Vec a(3);
    Vec b(3);

    a.data[0] = 1;
    a.data[1] = 0;
    a.data[2] = 0;

    b.data[0] = 2;
    b.data[1] = 0;
    b.data[2] = 0;

}
