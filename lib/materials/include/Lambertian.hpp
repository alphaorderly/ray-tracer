#pragma once

#include "Material.hpp"
#include "vec3.hpp"
#include "util.hpp"
#include "texture.hpp"
#include <memory>

namespace materials
{
    /**
     * Lambertian 재질은 완전한 난반사를 나타내는 재질입니다.
     * 이 재질은 들어오는 빛이 표면에 부딪힌 후 모든 방향으로 균일하게 산란된다고 가정합니다.
     * 따라서, Lambertian 재질은 매끄럽고 광택이 없는 표면을 모델링하는 데 적합합니다.
     */
    class Lambertian : public Material
    {
    public:
        explicit Lambertian(const raycore::Vec3 &albedo)
            : albedo_(albedo), texture_(nullptr) {}

        explicit Lambertian(std::shared_ptr<texture::Texture> tex)
            : albedo_(0, 0, 0), texture_(std::move(tex)) {}

        bool scatter(
            const raycore::Ray &rayIn,
            const shapes::HitRecord &record,
            raycore::Vec3 &attenuation,
            raycore::Ray &scattered) const override;

        const raycore::Vec3 &get_albedo() const { return albedo_; }

    private:
        raycore::Vec3 albedo_;                      ///< Surface reflectance color (used when texture_ == nullptr)
        std::shared_ptr<texture::Texture> texture_; ///< Optional texture
    };
}
