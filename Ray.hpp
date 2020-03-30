#pragma once

#include "Vec3.hpp"

class Ray
{
public:
    Vec3 o = {0,0,0};
    Vec3 d = {0,0,0};
    Vec3 pointAt(const double t) const;
};

