#pragma once

#include <vector>
#include <memory>
#include "Hittable.hpp"
#include "HitRecord.hpp"

namespace shapes {
    /**
     * @brief A list of hittable objects
     * 
     * This class manages a collection of hittable objects and provides
     * efficient intersection testing against all objects in the list.
     */
    class HittableList : public Hittable {
    public:
        HittableList() = default;
        HittableList(std::shared_ptr<Hittable> object) { add(object); }

        void clear() { objects_.clear(); }
        
        void add(std::shared_ptr<Hittable> object) {
            objects_.push_back(object);
        }

        bool hit(
            const raycore::Ray& r, 
            double tMin, 
            double tMax, 
            HitRecord& record
        ) const override;

        size_t size() const { return objects_.size(); }
        bool empty() const { return objects_.empty(); }

    private:
        std::vector<std::shared_ptr<Hittable>> objects_;
    };
}
