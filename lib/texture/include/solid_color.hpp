#pragma once

#include "texture.hpp"

namespace texture
{
    class SolidColor : public Texture
    {
    public:
        SolidColor() = default;
        explicit SolidColor(const raycore::Vec3 &color) : color_value(color) {}

        raycore::Vec3 value(double u, double v, const raycore::Vec3 &p) const override
        {
            return color_value;
        }

    private:
        raycore::Vec3 color_value{0, 0, 0};
    };
}
