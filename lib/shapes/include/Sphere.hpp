#pragma once

#include "Hittable.hpp"
#include "HitRecord.hpp"

#include <memory>

namespace shapes
{

    class Material;

    /**
     * @brief 구(Sphere) 기하 객체
     *
     * 구성 요소:
     * - 중심(center)
     * - 반지름(radius)
     * - 재질(material)
     */
    class Sphere : public Hittable
    {
    public:
        Sphere() = default;
        Sphere(const raycore::Vec3 &center, double radius, std::shared_ptr<materials::Material> material)
            : center_(center), radius_(radius), material_(material) {}

        bool hit(
            const raycore::Ray &r,
            double tMin,
            double tMax,
            HitRecord &record) const override;

        const raycore::Vec3 &get_center() const { return center_; }                     ///< 구 중심 반환
        double get_radius() const { return radius_; }                                   ///< 반지름 반환
        std::shared_ptr<materials::Material> get_material() const { return material_; } ///< 재질 반환

    private:
        raycore::Vec3 center_;                          ///< 구 중심
        double radius_;                                 ///< 반지름
        std::shared_ptr<materials::Material> material_; ///< 재질
    };
}
