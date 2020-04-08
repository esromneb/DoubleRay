#pragma once

#include "Vec3.hpp"
#include "Vec.hpp"
#include "RayEngine.hpp"
#include "Macros.hpp"
#include "Parser.hpp"

#include <functional>

// A bunch of naked functions

void setRayApiTarget(RayEngine* e);

extern "C" {

void setGlobalC(const int c);
void render(void);
// void doRender(void);
// void doDebugRender(void);
// uint32_t get4(void);
// uint32_t getNext(void);
void setScale(const double s);
// void debug2(void);
// void setFrameSleep(const int s);
void onRuntimeInitialized(void);
void onCustomMessage(void);
void coutInt(const int a);
void coutIntDual(const int a, const int b);
void setCamera(VEC3_ARG(location), VEC3_ARG(direction), VEC3_ARG(rotation));
void setDepth(const int d);
void setAmbientColor(VEC3_ARG(color));
void setNoHitColor(VEC3_ARG(color));
void setSphereCount(const int count);
void setSphere(const int index,
    const float radius,
    VEC3_ARG(location),
    const float ambient,
    const float specular,
    const float reflected,
    const float transmitted,
    VEC3_ARG(diffuse),
    float n,
    const float refraction);
void setLightCount(const int count);
void setLight(const int index,
    VEC3_ARG(direction),
    VEC3_ARG(color));
void dumpPoly(const int index);
void setHighlightPixel(const int x, const int y);
void setRefractShadows(const bool b);
void setEnableShadows(const bool b);
typedef std::function<void(void)> scene_animation_t;
void setupOrbit(const int _frames);
void nextOrbitRender(void);
void dumpCamera();
void chokeOutput(int il, int ih, int jl, int jh);
void setPrint(int p);
void parseJsonScene(const char* scene, const bool andRender );
void parseJsonSceneFragment(const std::string scene, const bool andRender );

} // extern C