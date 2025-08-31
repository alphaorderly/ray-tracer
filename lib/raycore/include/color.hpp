#pragma once

#include "vec3.hpp"

namespace raycore {
    raycore::vec3 sky_color(const raycore::vec3& direction) {
        double t = 0.5 * (direction.y + 1.0);
        return (1.0 - t) * raycore::vec3(1.0, 1.0, 1.0) + t * raycore::vec3(0.5, 0.7, 1.0);
    }
}