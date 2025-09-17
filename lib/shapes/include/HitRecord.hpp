#pragma once

#include "vec3.hpp"
#include "ray.hpp"
#include <memory>

namespace materials
{
    // 전방 선언: 상호 포함(circular dependency) 방지 목적
    class Material;
}

namespace shapes
{
    /**
     * @brief 광선(ray)과 표면이 교차(hit)했을 때의 정보를 저장하는 구조체
     *
     * 필드 설명:
     * - t: 교차 지점까지의 광선 매개변수(파라미터). r(t) = origin + t * direction 에서의 t.
     * - p: 교차 지점(world space 위치)
     * - normal: 교차 지점에서의 법선 벡터. 항상 광선의 진행 방향과 반대(외향) 방향을 바라보도록 set_face_normal 에서 조정.
     * - front_face: 광선이 표면의 앞면을 때렸는지 여부 (true = 앞면, false = 뒷면)
     * - material: 해당 지점에 적용되는 재질(Material)
     */
    struct HitRecord
    {
        double t;                                      ///< 교차 지점까지의 광선 매개변수 값
        raycore::Vec3 p;                               ///< 교차(world) 위치
        raycore::Vec3 normal;                          ///< 표면 법선(광선 방향 기준으로 외향으로 보정된 값)
        bool front_face;                               ///< 앞면(front) 적중 여부
        std::shared_ptr<materials::Material> material; ///< 표면 재질 포인터
        double u = 0.0;                                ///< 텍스처 좌표 U (0~1)
        double v = 0.0;                                ///< 텍스처 좌표 V (0~1)

        /**
         * @brief 광선이 표면을 때렸을 때 법선 방향을 일관되게(항상 외향) 설정한다.
         *
         * 구현 아이디어:
         * - 광선 방향과 outward_normal 의 내적이 음수이면 앞면을 친 것(front_face=true) → normal = outward_normal
         * - 양수이면 광선이 법선 방향과 같은 쪽에서 들어온 것(뒷면) → normal = -outward_normal
         *
         * 이렇게 하면 셰이딩 단계에서 법선이 항상 광선에 반대 방향이므로 산란 계산이 간단해진다.
         * @param r 입사 광선
         * @param outward_normal 기하학적으로 표면 외부를 향하는(정규화된) 법선 벡터
         */
        inline void set_face_normal(const raycore::Ray &r, const raycore::Vec3 &outward_normal)
        {
            front_face = raycore::dot(r.direction, outward_normal) < 0.0;
            normal = front_face ? outward_normal : -outward_normal;
        }
    };
}
