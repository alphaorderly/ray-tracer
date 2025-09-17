#pragma once

#include "Material.hpp"
#include "vec3.hpp"
#include "util.hpp"

namespace materials
{
    /**
     * Emmisive 재질은 빛을 방출하는 표면을 나타내는 재질입니다.
     * 이 재질은 표면에서 나오는 빛의 색상을 정의하며, 주로 광원이나 발광체를 모델링하는 데 사용됩니다.
     * Emmisive 재질은 빛을 산란시키지 않으며, 단순히 지정된 색상의 빛을 방출합니다.
     */
    class Emmisive : public Material
    {
    public:
        explicit Emmisive(const raycore::Vec3 &emitColor) : emitColor_(emitColor) {}

        bool scatter(
            const raycore::Ray &rayIn,
            const shapes::HitRecord &record,
            raycore::Vec3 &attenuation,
            raycore::Ray &scattered) const override
        {
            return false; // Emmisive materials do not scatter light
        }

        raycore::Vec3 emitted() const override
        {
            return emitColor_;
        }

        const raycore::Vec3 &get_emit_color() const { return emitColor_; }

    private:
        raycore::Vec3 emitColor_; ///< Color of the emitted light
    };
}