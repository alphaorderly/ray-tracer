#pragma once
#include <cmath>        // std::sqrt
#include <algorithm>    // std::clamp
#include <limits>       // std::numeric_limits

#include "vec3.hpp"
#include "ray.hpp"
#include "HittableList.hpp"
#include "Material.hpp"


namespace raycore {
    /**
     * @brief Get sky color gradient
     */
    inline Vec3 sky_color() {
        return Vec3(0.5, 0.7, 1.0);
    }
    
    /**
     * @brief get ray color with recursion
     */
    inline Vec3 ray_color(const Ray& r, const shapes::HittableList& world, int depth) {
        if (depth <= 0) {
            return Vec3(0, 0, 0); // No more light is gathered
        }

        shapes::HitRecord record;
        
        if (world.hit(r, 0.001, std::numeric_limits<double>::infinity(), record)) {
            Vec3 attenuation;
            Ray scattered(Vec3(0,0,0), Vec3(0,0,1)); // Initialize with default values
            
            if (record.material && record.material->scatter(r, record, attenuation, scattered)) {
                return attenuation * ray_color(scattered, world, depth - 1);
            }
            return Vec3(0, 0, 0); // Absorbed
        }

        Vec3 unit_direction = r.direction.normalize();
        double t = 0.5 * (unit_direction.y + 1.0);
        return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * sky_color();
    }
}
