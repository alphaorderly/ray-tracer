#pragma once

#include "ray.hpp"
#include "HitRecord.hpp"

namespace shapes
{
    /**
     * @brief 광선과 교차 판정을 할 수 있는 모든 기하 객체의 추상 인터페이스
     *
     * 역할:
     * - 모든 도형(구, 평면, 메쉬 등)이 공통으로 제공해야 하는 hit 함수 계약을 정의.
     * - 다형성(polymorphism)을 통해 서로 다른 기하 객체를 동일한 컨테이너에 담아 처리 가능.
     */
    class Hittable
    {
    public:
        virtual ~Hittable() = default;

        /**
         * @brief 광선이 객체와 교차하는지 검사한다.
         * @param r 검사 대상 광선
         * @param tMin 허용하는 t 범위의 하한 (너무 가까운 자기 교차 방지 등)
         * @param tMax 허용하는 t 범위의 상한 (더 가까운 교차가 이미 존재할 때 탐색 제한 등)
         * @param record 교차 시 교차 정보를 채워 반환할 구조체
         * @return [tMin, tMax] 구간 내에서 교차가 존재하면 true, 아니면 false
         */
        virtual bool hit(
            const raycore::Ray &r,
            double tMin,
            double tMax,
            HitRecord &record) const = 0;
    };
}
