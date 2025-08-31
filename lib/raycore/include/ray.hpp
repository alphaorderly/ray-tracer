#pragma once

#include "vec3.hpp"

namespace raycore {
    struct ray {
        vec3 origin;
        vec3 direction;

        ray(vec3 origin, vec3 direction) : origin(origin) {
            this->direction = direction.normalize();
        }

        vec3 at(double t) const {
            return origin + t * direction;
        }
    };
}