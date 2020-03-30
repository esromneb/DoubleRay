#pragma once

#include "Macros.hpp"
#include "Vec3.hpp"
#include "Poly.hpp"
#include "Matrix.hpp"
#include "Material.hpp"

#include <vector>

using namespace::std;




class Light
{
public:
    Vec3 color;
    Vec3 d;
};

class Ray
{
public:
    explicit Ray();
    Vec3 o;
    Vec3 d;
};

class Sphere
{
public:
    double r; //radius
    Vec3 c; //center
    Material m;
};



class RayEngine
{

public:
    RayEngine( void );
    void makeObjects( void );
    // void scene1( void );
    // void scene2( void );
    // void scene3( void );
    void paint( void );
    void render( void );
    bool trace(
        const Ray& r, 
        const int depthIn,
        Vec3 &color,
        const bool shdFeeling );

    Ray camera;
    Vec3 up;
    int x, y; //pixels
    // double alpha; // what is this for?

    //void setxy( int xin, int yin ); //resize output image

    void resize( const int _x );
    float *r, *g, *b;
    int px;
    Vec3 ia; // Ambient color
    double c;
    std::vector<Sphere> spheres;
    // int nSphere = 5;

    std::vector<Light> lights;
    // Light lights[2];
    // int nLight = 2;
    int depth;

    int numPoly = 0;
    vector<Poly> polygons;

    Matrix *mat;
    // vector<double> hits;
    // int numHit;

    // int il = 198;
    // int ih = 200;
    // int jl = 219;
    // int jh = 222;

    int il = 0;
    int ih = 500;
    int jl = 0;
    int jh = 500;

    bool print = false;

};

