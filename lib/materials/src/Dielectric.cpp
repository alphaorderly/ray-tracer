#include "Dielectric.hpp"
#include "HitRecord.hpp"

namespace materials {
    bool Dielectric::scatter(const raycore::Ray& rayIn,
                         const shapes::HitRecord& rec,
                         raycore::Vec3& attenuation,
                         raycore::Ray& scattered) const {

        attenuation = raycore::Vec3(1.0, 1.0, 1.0); 

        double etai_over_etat = rec.front_face ? (1.0 / ir) : ir;  


        raycore::Vec3 unit_dir = rayIn.direction.normalize();
        const raycore::Vec3& n = rec.normal;


        double cos_theta = std::fmin(raycore::dot(-unit_dir, n), 1.0);
        double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);
        bool cannot_refract = etai_over_etat * sin_theta > 1.0;

        raycore::Vec3 dir;
        if (cannot_refract || reflectance(cos_theta, ir) > raycore::random_double()) {
            dir = raycore::reflect(unit_dir, n);
        } else {
            dir = raycore::refract(unit_dir, n, etai_over_etat);
        }

        scattered = raycore::Ray(rec.p, dir);
        return true;
    }

    double Dielectric::reflectance(double cosine, double ior) const {
        double r0 = (1.0 - ior) / (1.0 + ior);
        r0 *= r0;
        return r0 + (1.0 - r0) * std::pow(1.0 - cosine, 5.0); // Schlick
    }

}