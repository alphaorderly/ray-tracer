#include "Metal.hpp"
#include "HitRecord.hpp"

namespace materials {
    bool Metal::scatter(
        const raycore::Ray& rayIn, 
        const shapes::HitRecord& record, 
        raycore::Vec3& attenuation, 
        raycore::Ray& scattered
    ) const {
        raycore::Vec3 unit_dir = rayIn.direction.normalize();
        raycore::Vec3 reflected = raycore::reflect(unit_dir, record.normal);
        
        // Add fuzziness to the reflection
        raycore::Vec3 scattered_direction = reflected + fuzz_ * raycore::random_in_unit_sphere();
        
        // Ensure the scattered direction is properly normalized
        if (raycore::near_zero(scattered_direction)) {
            scattered_direction = reflected;
        }
        scattered_direction = scattered_direction.normalize();
        
        scattered = raycore::Ray(record.p, scattered_direction);
        attenuation = albedo_;

        // Only scatter if the ray doesn't go below the surface
        return raycore::dot(scattered_direction, record.normal) > 0.0;
    }
}
