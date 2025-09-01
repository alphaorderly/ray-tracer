#pragma once

#include "ray.hpp"
#include "hit_record.hpp"

namespace hit {
    struct hittable {
        virtual ~hittable() = default;

        virtual bool hit(const raycore::ray& r, double t_min, double t_max, hit::hit_record& rec) const = 0;
    };
}