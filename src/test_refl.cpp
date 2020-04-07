#include "Vec3.hpp"

#include <iostream>
#include <cmath>

using namespace std;



int main(void) {
    cout << "foo\n";


    Vec3 ray(0,1,1);
    ray.normalize();

    Vec3 norm(0,-1,0);
    norm.normalize();

    cout << "Ray :\n" << ray.str() << "\n";
    cout << "Norm:\n" << norm.str() << "\n";

    Vec3 reflected = Vec3::reflect(ray, norm);

    cout << "Refl:\n" << reflected.str() << "\n";



    // c.rot_x(0.4);
}


// Annoying but required for now in the tests until we fix the RayApi
extern "C" {
void doRenderOfficial() {
}
}
