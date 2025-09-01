#pragma once

#include "vec3.hpp"
#include "ray.hpp"

namespace raycore {
    raycore::vec3 sky_color(const raycore::ray& r) {
        double t = 0.5 * (r.direction.y + 1.0);
        return (1.0 - t) * raycore::vec3(1.0, 1.0, 1.0) + t * raycore::vec3(0.5, 0.7, 1.0);
    }
}