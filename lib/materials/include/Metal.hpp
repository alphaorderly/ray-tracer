#pragma once

#include "Material.hpp"
#include "vec3.hpp"
#include "util.hpp"
#include <algorithm>

namespace materials
{
    /**
     * Metal 재질의 특징
     * - 반사율(albedo)과 거칠기(fuzz)를 속성으로 가짐
     * - 반사율은 표면이 빛을 얼마나 반사하는지를 나타냄
     * - 거칠기는 표면의 거칠기를 나타내며, 0은 완벽한 거울, 1은 매우 거친 표면을 의미함
     */
    class Metal : public Material
    {
    public:
        explicit Metal(const raycore::Vec3 &albedo, double fuzz = 0.0)
            : albedo_(albedo), fuzz_(std::clamp(fuzz, 0.0, 1.0)) {}

        bool scatter(
            const raycore::Ray &rayIn,
            const shapes::HitRecord &record,
            raycore::Vec3 &attenuation,
            raycore::Ray &scattered) const override;

        const raycore::Vec3 &get_albedo() const { return albedo_; }
        double get_fuzz() const { return fuzz_; }

    private:
        raycore::Vec3 albedo_; ///< Surface reflectance color
        double fuzz_;          ///< Surface roughness (0 = perfect mirror, 1 = very rough)
    };
}
