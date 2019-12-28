#ifndef _RAYTRACE_H_
#define _RAYTRACE_H_

#include <vector>
// #include <QGLWidget>
#include "vec3.h"

using namespace::std;


#define VERTS 1000
#define TRIANGLES 4000
#define POLYGONS 5

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
class Poly
{
    public:
    int num, numNorm; //should end out the same
    vector<double> x;
    vector<double> y;
    vector<double> z;

    vector<vec3> norm;
    vector<vec3> triNorm;

    vector<double> red;
    vector<double> green;
    vector<double> blue;

    vector<double> intensity;
    bool dontDraw[TRIANGLES/3];
    //vector<int> edges; //this will be sized num*2 cause the edges are stored in index 0,1 and 2,3 etc...
    vector<int> triangles;
    int edgeCount;
    void insert( float Xin, float Yin, float Zin );
    void insertNorm( float Xin, float Yin, float Zin );
    void insertTriangle( int *edges, int num );
    int trianglePointCount;
    void translate( float tx, float ty, float tz );
    void scale( float px, float py, float pz, float sx, float sy, float sz );
    void rotate( double px, double py, double theta );
/*    void rot_free( vec p1, vec p2, double theta );
    void rot_x( double theta );
    void rot_y( double theta );
    void rot_z( double theta );
//    void matrixMult( matrix &in );
    void old_rast(void);
    void rast( int view );

    */
    void setNorm(int which);
//    void color( int tri0, int x, int y, vector<double>* viewX, vector<double>* viewY, float &r, float &g, float &b ); //the triangle index of the 0th vert
    void findIntensity(int tri0, int x, int y, vector<double>* viewX, vector<double>* viewY, float &intensity);
    float area; //MUST BE UPDATED before calling color  This float has no meanning otherwise

    //lighting stuff
    void calcLighting( vector<double>* viewX, vector<double>* viewY, int view );
    float ka, ks, kr, kt;
    vec3 kd;
    int n;
    /*vector<double> a;
    vector<double> b;
    vector<double> c;*/
    vector<vec3> abcnorm;
    vector<double> d;
    //double a,b,c,d;

    Poly();
    ~Poly();
};


class rayEngine
{

public:
    explicit rayEngine( void );
    void makeObjects( void );
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
    static const int nSphere = 5;
    light lights[2];
    static const int nLight = 2;
    int depth;

    int numPoly;
    vector<Poly> polygons;

    matrix *mat;
    vector<double> hits;
    int numHit;

};


#endif
