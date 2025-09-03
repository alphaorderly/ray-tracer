#pragma once

#include "Material.hpp"
#include "vec3.hpp"
#include "util.hpp"

namespace materials {
    class Dielectric : public Material {
    public:
        Dielectric(double index_of_refraction) : ir(index_of_refraction) {}

        virtual bool scatter(const raycore::Ray& ray, const shapes::HitRecord& rec, raycore::Vec3& attenuation, raycore::Ray& scattered) const override;

        double reflectance(double cosine, double ref_idx) const;    

    private:
        double ir;  // Index of refraction
    };
}