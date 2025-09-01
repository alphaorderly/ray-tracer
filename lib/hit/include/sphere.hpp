#pragma once

#include <hittable.hpp>
#include <hit_record.hpp>

namespace hit {
    struct Sphere: public hit::hittable {
    public:
        Sphere() = default;
        Sphere(const raycore::vec3& cen, double r): center(cen), radius(r) {}

        virtual bool hit(const raycore::ray& r, double t_min, double t_max, hit_record& rec) const override;

    private:
        raycore::vec3 center;
        double radius;
    };
}