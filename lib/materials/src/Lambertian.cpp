#include "Lambertian.hpp"
#include "HitRecord.hpp"

namespace materials {
    bool Lambertian::scatter(
        const raycore::Ray& rayIn, 
        const shapes::HitRecord& record, 
        raycore::Vec3& attenuation, 
        raycore::Ray& scattered
    ) const {
        raycore::Vec3 scatter_direction = record.normal + raycore::random_unit_vector();

        // Catch degenerate scatter direction
        if (raycore::near_zero(scatter_direction)) {
            scatter_direction = record.normal;
        }

        scattered = raycore::Ray(record.p, scatter_direction);
        attenuation = albedo_;
        return true;
    }
}
