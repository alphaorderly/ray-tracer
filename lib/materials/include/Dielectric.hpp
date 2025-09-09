#pragma once

#include "Material.hpp"
#include "vec3.hpp"
#include "util.hpp"

namespace materials
{
    /**
     * 유리와 같은 유전체 물질의 머티리얼 클래스
     * 굴절률 (Index of Refraction, IOR) 을 사용하여 굴절과 반사를 계산
     * Schlick 근사를 사용하여 반사 확률을 결정
     * 굴절률이 1.0보다 크면 (예: 유리, 물) 굴절이 발생하고, 1.0보다 작으면 (예: 공기) 반사가 더 우세
     */
    class Dielectric : public Material
    {
    public:
        Dielectric(double index_of_refraction) : ir(index_of_refraction) {}

        virtual bool scatter(const raycore::Ray &ray, const shapes::HitRecord &rec, raycore::Vec3 &attenuation, raycore::Ray &scattered) const override;

        double reflectance(double cosine, double ref_idx) const;

    private:
        double ir; // Index of refraction
    };
}