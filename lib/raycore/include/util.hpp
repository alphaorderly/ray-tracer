#pragma once

#include <random>
#include <ctime>
#include <cmath>
#include "vec3.hpp"

namespace raycore {
    /**
     * @brief Generate a random double in the given range
     */
    inline double random_double(double min = 0.0, double max = 1.0) {
        static std::mt19937_64 rng(static_cast<unsigned>(time(nullptr)));
        std::uniform_real_distribution<double> dist(min, max);
        return dist(rng);
    }

    /**
     * @brief Generate a random vector inside a unit sphere
     */
    inline Vec3 random_in_unit_sphere() {
        while (true) {
            Vec3 p = Vec3(random_double(-1, 1), random_double(-1, 1), random_double(-1, 1));
            if (p.length_squared() >= 1.0) continue;
            return p;
        }
    }

    /**
     * @brief Generate a random unit vector
     */
    inline Vec3 random_unit_vector() {
        return random_in_unit_sphere().normalize();
    }

    /**
     * @brief Check if a vector is near zero in all dimensions
     */
    inline bool near_zero(const Vec3& v) {
        constexpr double epsilon = 1e-8;
        return (std::abs(v.x) < epsilon) && (std::abs(v.y) < epsilon) && (std::abs(v.z) < epsilon);
    }

    /**
     * @brief Reflect a vector about a normal
     */
    inline Vec3 reflect(const Vec3& v, const Vec3& n) {
        return v - 2 * dot(v, n) * n;
    }

    /**
     * @brief Refract a vector through a surface
     */
    inline Vec3 refract(const Vec3& v, const Vec3& n, double etai_over_etat) {
        Vec3 uv = v.normalize();
        double dt = dot(uv, n);
        double discriminant = 1.0 - etai_over_etat * etai_over_etat * (1.0 - dt * dt);
        if (discriminant > 0) {
            return etai_over_etat * (uv - n * dt) - n * std::sqrt(discriminant);
        }
        return Vec3();
    }

    /**
     * @brief Schlick's approximation for reflectance
     */
    inline double schlick(double cosine, double refractive_index) {
        double r0 = (1.0 - refractive_index) / (1.0 + refractive_index);
        r0 = r0 * r0;
        return r0 + (1.0 - r0) * std::pow(1.0 - cosine, 5);
    }

}
