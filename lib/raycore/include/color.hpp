#pragma once
#include <cmath>     // std::sqrt
#include <algorithm> // std::clamp
#include <limits>    // std::numeric_limits

#include "vec3.hpp"
#include "ray.hpp"
#include "HittableList.hpp"
#include "Material.hpp"

namespace raycore
{
    /**
     * 배경색 (하늘색) 반환
     */
    inline Vec3 sky_color()
    {
        return Vec3(0.5, 0.7, 1.0);
    }

    /**
     * 광선과 오브젝트들이 주어졌을때, 광선이 오브젝트와 충돌하는지 확인하고
     * 충돌한다면 그 지점에서의 색상을 계산하여 반환
     */
    inline Vec3 ray_color(const Ray &r, const shapes::HittableList &world, int depth)
    {
        // 방어적 코드: 재귀 깊이가 0 이하가 되면 더 이상 빛을 수집하지 않음
        if (depth <= 0)
        {
            return Vec3(0, 0, 0); // No more light is gathered
        }

        // 광선이 오브젝트와 충돌하는지 확인하기 위한 히트 레코드
        shapes::HitRecord record;

        // 충돌 검사
        /**
         * 0.001은 tMin으로, 너무 가까운 충돌(예: 자기 자신과의 충돌)을 방지하기 위한 작은 값
         * std::numeric_limits<double>::infinity()는 tMax으로, 사실상 무한대의 거리를 의미
         */
        if (world.hit(r, 0.001, std::numeric_limits<double>::infinity(), record))
        {
            Vec3 attenuation;
            Ray scattered(Vec3(0, 0, 0), Vec3(0, 0, 1)); // Initialize with default values

            // 재질이 존재하고, 반사광이 있다면 재귀적으로 색상 계산
            if (record.material && record.material->scatter(r, record, attenuation, scattered))
            {
                return attenuation * ray_color(scattered, world, depth - 1);
            }
            return record.material->emitted();
        }

        // 광선이 어떤 오브젝트와도 충돌하지 않았다면, 배경색(하늘색)을 반환
        Vec3 unit_direction = r.direction.normalize();
        // 자연스러운 그라데이션 효과를 위해 y 성분을 사용
        double t = 0.5 * (unit_direction.y + 1.0);
        return (1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * sky_color();
    }
}
