#ifndef _RAYTRACE_H_
#define _RAYTRACE_H_

#include <vector>
// #include <QGLWidget>
#include "vec3.h"
#include "Poly.hpp"
#include "Macros.hpp"

using namespace::std;



class matrix {
public:
    int x;
    int y;
    matrix( int xin, int yin );
    ~matrix( void );
//    vec operator* ( vec &rhs );
    double ** data;
    double det( void );
    matrix *m1, *m2, *m3;
};

class light
{
public:
    vec3 color;
    vec3 d;
};

class ray
{
public:
    explicit ray();
    vec3 o;
    vec3 d;
};

class sphere
{
public:
    double r; //radius
    vec3 c; //center
    // %ambient, %specular, %reflected, %transmitted
    float ka, ks, kr, kt;
    // %diffuse (also specifies color of this object)
    vec3 kd;
    int n;
};



class rayEngine
{

public:
    rayEngine( void );
    void makeObjects( void );
    void scene1( void );
    void scene2( void );
    void scene3( void );
    void paint( void );
    void render( void );
    void trace( ray r, int depthIn, double effect, vec3 &color, bool click, bool &bSphere, vec3 &objectNum, bool shdFeeling );

    ray camera;
    vec3 up;
    int x, y; //pixels
    double alpha;
    //void setxy( int xin, int yin ); //resize output image
    void resize( int x );
    float *r,*g, *b;
    int px;
    vec3 ia;
    double c;
    sphere spheres[8];
    int nSphere = 5;
    light lights[2];
    int nLight = 2;
    int depth;

    int numPoly;
    vector<Poly> polygons;

    matrix *mat;
    vector<double> hits;
    int numHit;

};


#endif
