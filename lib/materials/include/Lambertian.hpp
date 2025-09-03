#pragma once

#include "Material.hpp"
#include "vec3.hpp"
#include "util.hpp"

namespace materials {
    /**
     * @brief Lambertian (diffuse) material implementation
     * 
     * Lambertian materials scatter incoming light uniformly in all directions
     * above the surface, creating a matte appearance.
     */
    class Lambertian : public Material {
    public:
        explicit Lambertian(const raycore::Vec3& albedo) : albedo_(albedo) {}

        bool scatter(
            const raycore::Ray& rayIn, 
            const shapes::HitRecord& record, 
            raycore::Vec3& attenuation, 
            raycore::Ray& scattered
        ) const override;

        const raycore::Vec3& get_albedo() const { return albedo_; }

    private:
        raycore::Vec3 albedo_;  ///< Surface reflectance color
    };
}
