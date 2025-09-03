#pragma once

#include "vec3.hpp"
#include "ray.hpp"
#include <memory>

namespace materials {
    // Forward declaration to avoid circular dependency
    class Material;
}

namespace shapes {
    /**
     * @brief Records information about a ray-surface intersection
     */
    struct HitRecord {
        double t;                               ///< Ray parameter at intersection
        raycore::Vec3 p;                        ///< Point of intersection
        raycore::Vec3 normal;                   ///< Surface normal at intersection
        bool front_face;                        ///< Whether ray hit front face
        std::shared_ptr<materials::Material> material; ///< Material at intersection

        /**
         * @brief Sets the face normal based on ray direction
         * @param r The incoming ray
         * @param outward_normal The outward normal from the surface
         */
        inline void set_face_normal(const raycore::Ray& r, const raycore::Vec3& outward_normal) {
            front_face = raycore::dot(r.direction, outward_normal) < 0.0;
            normal = front_face ? outward_normal : -outward_normal;
        }
    };
}
