#pragma once

#include <vector>
#include <memory>
#include "Hittable.hpp"
#include "HitRecord.hpp"

namespace shapes
{
    /**
     * @brief 여러 개의 Hittable 객체를 보관/관리하는 컨테이너
     *
     * 단순 구현:
     * - 내부적으로 std::vector<shared_ptr<Hittable>> 로 객체를 저장.
     * - hit 호출 시 모든 객체를 순회하여 가장 가까운(최소 t) 교차를 찾는다.
     *   (BVH 같은 가속구조는 아직 적용하지 않은 브루트포스 방식)
     */
    class HittableList : public Hittable
    {
    public:
        HittableList() = default;
        HittableList(std::shared_ptr<Hittable> object) { add(object); }

        void clear() { objects_.clear(); } ///< 모든 객체 제거

        void add(std::shared_ptr<Hittable> object)
        { ///< 객체 추가
            objects_.push_back(object);
        }

        bool hit(
            const raycore::Ray &r,
            double tMin,
            double tMax,
            HitRecord &record) const override;

        size_t size() const { return objects_.size(); } ///< 포함된 객체 수
        bool empty() const { return objects_.empty(); } ///< 비었는지 여부

    private:
        std::vector<std::shared_ptr<Hittable>> objects_; ///< 도형 목록
    };
}
