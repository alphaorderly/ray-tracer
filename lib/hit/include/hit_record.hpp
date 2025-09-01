#pragma once

#include "vec3.hpp"
#include "ray.hpp"

namespace hit {
    struct hit_record {
        double t;
        raycore::vec3 p;
        raycore::vec3 normal;
        bool front_face;

        inline void set_face_normal(const raycore::ray& r, const raycore::vec3& outward_normal) {
            front_face = raycore::dot(r.direction, outward_normal) < 0;
            normal = front_face ? outward_normal : -outward_normal;
        }
    };
}