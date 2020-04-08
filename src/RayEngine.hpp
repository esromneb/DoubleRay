#pragma once

#include "Macros.hpp"
#include "Vec3.hpp"
#include "Poly.hpp"
// #include "Matrix.hpp"
#include "Material.hpp"
#include "Ray.hpp"

#include <vector>

using namespace::std;

// #define ALLOW_PRINT
// #define ALLOW_CHOKE
// #define ALLOW_HIGHLIGHT


class Light
{
public:
    Vec3 color;
    Vec3 d;
    constexpr static Vec3 defaultDirection = {0,0,-1};
    constexpr static Vec3 defaultColor = {20,20,20};
};


class Sphere
{
public:
    double r; //radius
    Vec3 c; //center
    Material m;
    double r_inv;
    double r_sq;
    void constexpr calc(void) { r_inv = 1.0/r; r_sq = r*r; };
};

// forward declare and type so that RayEngine can render to pixels 100% internally
class SDL_PixelFormat;
typedef uint32_t (*wasm_gl_pixel_t)(const SDL_PixelFormat*, uint8_t, uint8_t, uint8_t);


class RayEngine
{

public:
    RayEngine( void );

    void render( void ) noexcept;

    template <bool enableShadowsT, bool refractShadowsT>
    void _render( void ) noexcept;

    template <bool enableShadowsT, bool refractShadowsT, bool shadowFeelingT>
    std::tuple<bool,double> trace(
        const Ray& r, 
        const int depthIn,
        Vec3 &color) noexcept;

    Ray camera;
    Vec3 up;

    // unsigned int xPx, yPx; // Dimensions of output in pixels

    //void setxy( int xin, int yin ); //resize output image

    void resize( const int _x );

    float *rBuffer = 0;
    float *gBuffer = 0;
    float *bBuffer = 0;

    int px = 0;
    Vec3 ia; // Ambient color
    Vec3 noHitColor = {0,0,0}; // What color if don't hit anything?
    double c;
    std::vector<Sphere> spheres;

    std::vector<Light> lights;
    int depth = 0;

    int numPoly = 0;
    vector<Poly> polygons;

    // Matrix *mat = 0;
    // vector<double> hits;
    // int numHit;

    // int il = 198;
    // int ih = 200;
    // int jl = 219;
    // int jh = 222;

#ifdef ALLOW_CHOKE
    int il = -1;
    int ih = 500;
    int jl = -1;
    int jh = 500;
#endif

#ifdef ALLOW_HIGHLIGHT
    int highlightX = -1;
    int highlightY = -1;
#endif

#ifdef ALLOW_PRINT
    bool print = false;
#endif

    constexpr static double defaultScale = 255;
    constexpr static bool defaultMemberRefractShadows = true;
    constexpr static bool defaultEnableShadows = true;

    ///
    /// these should not be read inside render() or trace()
    /// instead these should be read and then used to choose
    /// which template to call
    ///
    /// This option determines if we do fancy refraction of shadows
    /// for objects that have transmission
    bool memberRefractShadows = defaultMemberRefractShadows;

    /// do we calculate shadows at all
    bool enableShadows = defaultEnableShadows;

    // Factor used to scale in-engine floating point colors
    // to 0-255 rgb
    double scale = defaultScale;




    // copy internal state to pixel buffer for WASM
    void copyToPixels(wasm_gl_pixel_t fn, void* const pixels, void* const format) const;

    // copy internal state to pixel buffer for PNG
    void copyToPixels(std::vector<unsigned char>& buffer) const;
};

