#pragma once

#include <random>
#include <ctime>
#include <cmath>
#include "vec3.hpp"

namespace raycore
{
    /**
     * @brief Generate a random double in the given range
     */
    inline double random_double(double min = 0.0, double max = 1.0)
    {
        static std::mt19937_64 rng(static_cast<unsigned>(time(nullptr)));
        std::uniform_real_distribution<double> dist(min, max);
        return dist(rng);
    }

    /**
     * @brief Generate a random vector inside a unit sphere
     */
    inline Vec3 random_in_unit_sphere()
    {
        while (true)
        {
            Vec3 p = Vec3(random_double(-1, 1), random_double(-1, 1), random_double(-1, 1));
            if (p.length_squared() >= 1.0)
                continue;
            return p;
        }
    }

    /**
     * @brief Generate a random unit vector
     */
    inline Vec3 random_unit_vector()
    {
        return random_in_unit_sphere().normalize();
    }

    /**
     * @brief Check if a vector is near zero in all dimensions
     */
    inline bool near_zero(const Vec3 &v)
    {
        constexpr double epsilon = 1e-8;
        return (std::abs(v.x) < epsilon) && (std::abs(v.y) < epsilon) && (std::abs(v.z) < epsilon);
    }

    /**
     * 법선벡터인 n 에 대한 벡터 v의 이상적 반사벡터를 반환한다.
     */
    inline Vec3 reflect(const Vec3 &v, const Vec3 &n)
    {
        return v - 2 * dot(v, n) * n;
    }

    /**
     * @brief       표면에서 벡터를 굴절시키는 함수
     * @param v     입사 벡터 (the incident vector)
     * @param n     표면의 법선 벡터 (the surface normal)
     * @param etai_over_etat 굴절률의 비율 (η_i / η_t)
     * @return      굴절된 벡터. 내부 전반사가 일어나면 영벡터를 반환.
     */
    inline Vec3 refract(const Vec3 &v, const Vec3 &n, double etai_over_etat)
    {
        // 입사광선 벡터를 정규화하여 단위 벡터로 만든다.
        Vec3 uv = v.normalize();

        // uv와 법선 벡터 n의 내적을 계산한다. 이는 두 벡터 사이 각도의 코사인 값(cosθ)과 같다.
        // 두 벡터 모두 단위 벡터이므로 |uv| = 1, |n| = 1이다.
        double dt = dot(uv, n);

        // 스넬의 법칙을 벡터 형태로 계산하기 위한 판별식(discriminant)을 구한다.
        // 판별식 = 1.0 - (η_i/η_t)² * (1 - cos²θ_i) = 1.0 - (η_i/η_t)² * sin²θ_i
        // 스넬의 법칙(η_i * sinθ_i = η_t * sinθ_t)에 의해 위 식은 1.0 - sin²θ_t = cos²θ_t 가 된다.
        double discriminant = 1.0 - etai_over_etat * etai_over_etat * (1.0 - dt * dt);

        // 판별식이 0보다 크면, 즉 실수 해가 존재하면 굴절이 일어난다.
        if (discriminant > 0)
        {
            // 스넬의 법칙(벡터 형태)을 이용해 굴절 광선 벡터를 계산하고 반환한다.
            // 굴절 벡터 R' = (η_i/η_t) * (R + n*cosθ_i) - n*cosθ_t
            // 여기서 R은 입사 벡터, n은 법선 벡터이다.
            return etai_over_etat * (uv - n * dt) - n * std::sqrt(discriminant);
        }

        // 판별식이 0보다 작거나 같으면 내부 전반사(total internal reflection)가 발생한 것이다.
        // 이 경우 굴절 광선은 존재하지 않으므로 영벡터(zero vector)를 반환한다.
        return Vec3();
    }

    /**
     * @brief Schlick's approximation for reflectance
     */
    inline double schlick(double cosine, double refractive_index)
    {
        double r0 = (1.0 - refractive_index) / (1.0 + refractive_index);
        r0 = r0 * r0;
        return r0 + (1.0 - r0) * std::pow(1.0 - cosine, 5);
    }

    inline double clamp(double x, double min, double max)
    {
        return std::max(min, std::min(max, x));
    }

}
