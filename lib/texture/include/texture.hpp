#pragma once

#include "vec3.hpp"

namespace texture
{
    struct Texture
    {
        virtual ~Texture() = default;
        virtual raycore::Vec3 value(double u, double v, const raycore::Vec3 &p) const = 0;
    };
}