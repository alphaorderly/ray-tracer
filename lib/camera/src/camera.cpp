#include "camera.hpp"

namespace camera {
    raycore::ray Camera::getRay(double s, double t) const {
        return raycore::ray(
            origin,
            lowerLeftCorner + s * horizontal + t * vertical - origin
        );
    }
}
