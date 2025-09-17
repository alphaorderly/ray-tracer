#pragma once

#include "texture.hpp"

namespace texture
{
    class Checker : public Texture
    {
    public:
        Checker(std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd)
            : even_(std::move(even)), odd_(std::move(odd)) {}

        raycore::Vec3 value(double u, double v, const raycore::Vec3 &p) const override
        {
            double sines = std::sin(10 * p.x) * std::sin(10 * p.y) * std::sin(10 * p.z);
            if (sines < 0)
                return odd_->value(u, v, p);
            else
                return even_->value(u, v, p);
        }

    private:
        std::shared_ptr<Texture> even_;
        std::shared_ptr<Texture> odd_;
    };
}