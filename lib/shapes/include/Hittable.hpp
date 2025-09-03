#pragma once

#include "ray.hpp"
#include "HitRecord.hpp"

namespace shapes {
    /**
     * @brief Abstract interface for objects that can be hit by rays
     * 
     * This interface defines the contract for all geometric objects
     * in the ray tracer.
     */
    class Hittable {
    public:
        virtual ~Hittable() = default;

        /**
         * @brief Test if a ray hits this object
         * 
         * @param r The ray to test
         * @param tMin Minimum ray parameter to consider
         * @param tMax Maximum ray parameter to consider
         * @param record Output parameter for hit information
         * @return true if hit occurs within [tMin, tMax], false otherwise
         */
        virtual bool hit(
            const raycore::Ray& r, 
            double tMin, 
            double tMax, 
            HitRecord& record
        ) const = 0;
    };
}
