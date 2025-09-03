#pragma once

#include "Hittable.hpp"
#include "HitRecord.hpp"

#include <memory>

namespace shapes {

    class Material;

    /**
     * @brief A sphere geometric object
     * 
     * Represents a sphere with center, radius, and material properties.
     */
    class Sphere : public Hittable {
    public:
        Sphere() = default;
        Sphere(const raycore::Vec3& center, double radius, std::shared_ptr<materials::Material> material)
            : center_(center), radius_(radius), material_(material) {}

        bool hit(
            const raycore::Ray& r, 
            double tMin, 
            double tMax, 
            HitRecord& record
        ) const override;

        const raycore::Vec3& get_center() const { return center_; }
        double get_radius() const { return radius_; }
        std::shared_ptr<materials::Material> get_material() const { return material_; }

    private:
        raycore::Vec3 center_;                      ///< Center of the sphere
        double radius_;                             ///< Radius of the sphere
        std::shared_ptr<materials::Material> material_;  ///< Material of the sphere
    };
}
