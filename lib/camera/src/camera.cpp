#include "camera.hpp"

namespace camera {
    raycore::Ray Camera::getRay(double s, double t) const {
        return raycore::Ray(
            origin,
            lowerLeftCorner + s * horizontal + t * vertical - origin
        );
    }
}
