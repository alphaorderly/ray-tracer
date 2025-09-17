#include "Lambertian.hpp"
#include "HitRecord.hpp"

namespace materials
{
    bool Lambertian::scatter(
        const raycore::Ray &rayIn,
        const shapes::HitRecord &record,
        raycore::Vec3 &attenuation,
        raycore::Ray &scattered) const
    {
        // 빛이 산란되는 방향
        // 법선 벡터에 단위 구면에서 무작위로 선택된 벡터를 더함
        raycore::Vec3 scatter_direction = record.normal + raycore::random_unit_vector();

        // 산란 방향이 거의 0 벡터인 경우 (법선과 반대 방향으로 무작위 벡터가 나올 때)
        // 법선 벡터를 산란 방향으로 사용
        if (raycore::near_zero(scatter_direction))
        {
            scatter_direction = record.normal;
        }

        // 산란되는 광선 생성
        scattered = raycore::Ray(record.p, scatter_direction);
        if (texture_)
        {
            attenuation = texture_->value(record.u, record.v, record.p);
        }
        else
        {
            attenuation = albedo_;
        }
        return true;
    }
}
