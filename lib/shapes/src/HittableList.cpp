#include "HittableList.hpp"

namespace shapes
{
    bool HittableList::hit(
        const raycore::Ray &r,
        double tMin,
        double tMax,
        HitRecord &record) const
    {
        HitRecord tempRecord;       // 각 객체 교차 결과를 임시 저장
        bool hitAnything = false;   // 하나라도 맞았는지 여부
        double closestSoFar = tMax; // 지금까지 발견된 가장 가까운 t

        // 모든 객체 순회 (가속구조 미사용: O(N))
        for (const auto &object : objects_)
        {
            // closestSoFar 로 상한을 갱신하여 더 먼 교차는 무시
            if (object->hit(r, tMin, closestSoFar, tempRecord))
            {
                hitAnything = true;
                closestSoFar = tempRecord.t;
                record = tempRecord; // 가장 가까운 교차 정보 유지
            }
        }

        return hitAnything;
    }
}
