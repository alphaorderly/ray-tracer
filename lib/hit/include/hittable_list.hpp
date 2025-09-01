#pragma once

#include <vector>
#include <memory>

#include "hittable.hpp"
#include "hit_record.hpp"

namespace hit {
    class hittable_list: public hittable {
    public:
        hittable_list() = default;

        void add(std::shared_ptr<hittable> obj) {
            objects.push_back(obj);
        }

        bool hit(const raycore::ray& r, double t_min, double t_max, hit_record& rec) const;

    private:
        std::vector<std::shared_ptr<hittable>> objects{};
    };
}