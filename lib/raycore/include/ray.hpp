#pragma once

#include "vec3.hpp"

namespace raycore {
    struct Ray {
        Vec3 origin;
        Vec3 direction;

        Ray(Vec3 origin, Vec3 direction) : origin(origin) {
            this->direction = direction.normalize();
        }

        Vec3 at(double t) const {
            return origin + t * direction;
        }
    };
}