#include "Dielectric.hpp"
#include "HitRecord.hpp"

namespace materials
{

    /**
     *
     * @param rayIn 입사 광선
     * @param rec 충돌 정보
     * @param attenuation 감쇠 (반사/굴절 후 색상 변화), 즉 재질의 색상을 나타낸다.
     * @param scattered 산란된 광선 ( 결과 )
     */
    bool Dielectric::scatter(const raycore::Ray &rayIn,
                             const shapes::HitRecord &rec,
                             raycore::Vec3 &attenuation,
                             raycore::Ray &scattered) const
    {
        // 들어가는 빛의 매질의 굴절률 / 나오는 빛의 매질의 굴절률
        // front_face 가 true일시 공기 -> 해당 머티리얼 (1.0 / ir)
        // front_face 가 false일시 해당 머티리얼 -> 공기 (ir)
        double etai_over_etat = rec.front_face ? (1.0 / ir) : ir;

        // 입사되는 광선의 단위 방향 벡터와 법선 벡터
        raycore::Vec3 unit_dir = rayIn.direction.normalize();

        // n : 표면에 부딫힌 부분에 대한 법선 벡터
        const raycore::Vec3 &n = rec.normal;

        /**
         * 벡터의 내적은 두 벡터의 크기와 그 사이의 각도의 코사인값의 곱으로 정의됨
         * dot(a, b) = |a| * |b| * cos(theta)
         * 여기서 a와 b가 단위 벡터일 경우 |a| = |b| = 1 이므로
         * dot(a, b) = cos(theta)
         * 즉, 두 단위 벡터의 내적은 그 사이의 각도의 코사인값과 같음
         * 다만 fmin을 사용하여 1.0을 넘지 않도록 제한한다 ( 부동 소수점 오차 방지 )
         */
        double cos_theta = std::fmin(raycore::dot(-unit_dir, n), 1.0);

        /**
         * sin^2(theta) + cos^2(theta) = 1
         * sin(theta) = sqrt(1 - cos^2(theta))
         */
        double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

        /**
         * 굴절이 불가능한 경우 (전반사)
         * etai_over_etat * sin_theta > 1.0
         */
        bool cannot_refract = etai_over_etat * sin_theta > 1.0;

        raycore::Vec3 dir;

        if (cannot_refract || reflectance(cos_theta, ir) > raycore::random_double())
        {
            // 전반사가 일어날때  또는 슈링크 근사에 의한 반사 확률이 더 클때
            // 반사 벡터 계산
            dir = raycore::reflect(unit_dir, n);
        }
        else
        {
            // 굴절 벡터 계산
            dir = raycore::refract(unit_dir, n, etai_over_etat);
        }

        // 계산된 방향으로 산란된 광선 생성
        scattered = raycore::Ray(rec.p, dir);
        return true;
    }

    /**
     * 슈링크 근사(Schlick's approximation)를 사용하여 반사 확률을 계산
     * @param cosine 입사각의 코사인 값
     * @param ior 굴절률 (index of refraction)
     * @return 반사 확률 (0.0 ~ 1.0)
     */
    double Dielectric::reflectance(double cosine, double ior) const
    {
        double r0 = (1.0 - ior) / (1.0 + ior);
        r0 *= r0;
        return r0 + (1.0 - r0) * std::pow(1.0 - cosine, 5.0); // Schlick
    }

}