#include "Sphere.hpp"
#include <cmath>

namespace shapes {
    bool Sphere::hit(
        const raycore::Ray& r, 
        double tMin, 
        double tMax, 
        HitRecord& record
    ) const {
        raycore::Vec3 oc = r.origin - center_;
        double a = r.direction.length_squared();
        double half_b = raycore::dot(oc, r.direction);
        double c = oc.length_squared() - radius_ * radius_;

        double discriminant = half_b * half_b - a * c;
        if (discriminant < 0.0) {
            return false;
        }

        double sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range
        double root = (-half_b - sqrtd) / a;
        if (root < tMin || root > tMax) {
            root = (-half_b + sqrtd) / a;
            if (root < tMin || root > tMax) {
                return false;
            }
        }

        record.t = root;
        record.p = r.at(record.t);
        raycore::Vec3 outward_normal = (record.p - center_) / radius_;
        record.set_face_normal(r, outward_normal);
        record.material = material_;

        return true;
    }
}
