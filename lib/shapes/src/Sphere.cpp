#include "Sphere.hpp"
#include <cmath>
#include "util.hpp"

namespace shapes
{
    bool Sphere::hit(
        const raycore::Ray &r,
        double tMin,
        double tMax,
        HitRecord &record) const
    {
        // 구 방정식: |(O + tD) - C|^2 = R^2 → 2차 방정식 at^2 + bt + c = 0
        // 여기서 O: 광선 origin, D: direction, C: 구 중심
        raycore::Vec3 oc = r.origin - center_;              // O - C
        double a = r.direction.length_squared();            // D·D
        double half_b = raycore::dot(oc, r.direction);      // b/2 = (O-C)·D
        double c = oc.length_squared() - radius_ * radius_; // (O-C)·(O-C) - R^2

        double discriminant = half_b * half_b - a * c; // (b/2)^2 - a*c
        if (discriminant < 0.0)
        {
            return false; // 실근 없음 → 교차 없음
        }

        double sqrtd = std::sqrt(discriminant);

        // 허용 구간 [tMin, tMax] 안에 있는 더 작은 근(가까운 교차)부터 검사
        double root = (-half_b - sqrtd) / a;
        if (root < tMin || root > tMax)
        {
            root = (-half_b + sqrtd) / a; // 다른 근 검사
            if (root < tMin || root > tMax)
            {
                return false; // 둘 다 범위 밖
            }
        }

        record.t = root;
        record.p = r.at(record.t);                                     // 교차 위치
        raycore::Vec3 outward_normal = (record.p - center_) / radius_; // 기하학적 외향 법선
        record.set_face_normal(r, outward_normal);                     // 광선 기준으로 정방향 설정
        record.material = material_;                                   // 재질 기록

        // 구 표면에 대한 UV 좌표 계산 (표준 구 좌표계)
        // outward_normal 은 이미 (p - center)/radius 로 계산됨
        // theta: y축을 기준으로 한 각도 [0, pi]
        // phi: xz 평면에서의 방위각 [-pi, pi]
        double theta = std::acos(raycore::clamp(outward_normal.y, -1.0, 1.0));
        double phi = std::atan2(outward_normal.z, outward_normal.x);
        if (phi < 0)
            phi += 2 * M_PI; // [0, 2pi]
        record.u = phi / (2 * M_PI);
        record.v = 1.0 - theta / M_PI; // 위쪽이 v=1.0 이 되도록 반전

        return true;
    }
}
