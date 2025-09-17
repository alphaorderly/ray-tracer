#include "Metal.hpp"
#include "HitRecord.hpp"

namespace materials
{
    bool Metal::scatter(
        const raycore::Ray &rayIn,
        const shapes::HitRecord &record,
        raycore::Vec3 &attenuation,
        raycore::Ray &scattered) const
    {
        // 들어오는 광선
        raycore::Vec3 unit_dir = rayIn.direction.normalize();
        // 반사 벡터 계산 ( 매끈한 표면 기준 )
        raycore::Vec3 reflected = raycore::reflect(unit_dir, record.normal);

        // 거친 정도를 반영해 반사 벡터에 잡음 추가
        raycore::Vec3 scattered_direction = reflected + fuzz_ * raycore::random_in_unit_sphere();

        // 반사 방향이 0에 가까우면, 거친 정도를 반영하지 않은 반사 벡터 사용
        if (raycore::near_zero(scattered_direction))
        {
            scattered_direction = reflected;
        }

        // 반사 방향 정규화
        scattered_direction = scattered_direction.normalize();

        scattered = raycore::Ray(record.p, scattered_direction);
        attenuation = albedo_;

        // Only scatter if the ray doesn't go below the surface
        return raycore::dot(scattered_direction, record.normal) > 0.0;
    }
}
