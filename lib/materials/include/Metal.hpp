#pragma once

#include "Material.hpp"
#include "vec3.hpp"
#include "util.hpp"
#include <algorithm>

namespace materials {
    /**
     * @brief Metallic material implementation
     * 
     * Metal materials reflect incoming light with some amount of fuzziness
     * based on surface roughness.
     */
    class Metal : public Material {
    public:
        explicit Metal(const raycore::Vec3& albedo, double fuzz = 0.0) 
            : albedo_(albedo), fuzz_(std::clamp(fuzz, 0.0, 1.0)) {}

        bool scatter(
            const raycore::Ray& rayIn, 
            const shapes::HitRecord& record, 
            raycore::Vec3& attenuation, 
            raycore::Ray& scattered
        ) const override;

        const raycore::Vec3& get_albedo() const { return albedo_; }
        double get_fuzz() const { return fuzz_; }

    private:
        raycore::Vec3 albedo_;  ///< Surface reflectance color
        double fuzz_;           ///< Surface roughness (0 = perfect mirror, 1 = very rough)
    };
}
