#include "Ray.hpp"

Vec3 Ray::pointAt(const double t) const {
    return Vec3( o[0] + d[0]*t,
                 o[1] + d[1]*t,
                 o[2] + d[2]*t);
}
