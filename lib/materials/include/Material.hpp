#pragma once

#include "ray.hpp"
#include "vec3.hpp"
#include <memory>

namespace shapes {
    // Forward declaration to avoid circular dependency
    struct HitRecord;
}

namespace materials {
    /**
     * @brief Abstract base class for all materials in the ray tracer
     * 
     * Materials define how light interacts with surfaces, including
     * reflection, refraction, and absorption properties.
     */
    class Material {
    public:
        virtual ~Material() = default;

        /**
         * @brief Determines how a ray scatters when hitting a surface
         * 
         * @param rayIn The incoming ray
         * @param record The hit record containing surface information
         * @param attenuation The color attenuation factor
         * @param scattered The scattered ray
         * @return true if the ray scatters, false if absorbed
         */
    virtual bool scatter(
            const raycore::Ray& rayIn, 
            const shapes::HitRecord& record, 
            raycore::Vec3& attenuation, 
            raycore::Ray& scattered
    ) const = 0;
    };
}

