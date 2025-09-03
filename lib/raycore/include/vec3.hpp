#pragma once

#include <ostream>
#include <cmath>
#include <stdexcept>

namespace raycore {
    struct Vec3 {
        double x, y, z;

        Vec3() : x(0), y(0), z(0) {}
        Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

        // Binary operations
        Vec3 operator+(const Vec3& other) const {
            return Vec3{x + other.x, y + other.y, z + other.z};
        }

        Vec3 operator-(const Vec3& other) const {
            return Vec3{x - other.x, y - other.y, z - other.z};
        }

        // unary operations
        Vec3 operator-() const {
            return Vec3{-x, -y, -z};
        }

        // Scalar operations
        Vec3 operator*(double scalar) const {
            return Vec3{x * scalar, y * scalar, z * scalar};
        }

        Vec3 operator/(double scalar) const {
            // prevent division by zero
            if (scalar == 0.0) {
                throw std::runtime_error("Division by zero in Vec3");
            }
            return Vec3{x / scalar, y / scalar, z / scalar};
        }

        // +=, -=, *=, /=
        Vec3& operator+=(const Vec3& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Vec3& operator-=(const Vec3& other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        Vec3& operator*=(double scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        Vec3& operator/=(double scalar) {
            // prevent division by zero
            if (scalar == 0.0) {
                throw std::runtime_error("Division by zero in Vec3");
            }
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        // length, normalize
        double length() const {
            return std::sqrt(x * x + y * y + z * z);
        }

        double length_squared() const {
            return x * x + y * y + z * z;
        }

        Vec3 normalize() const {
            double len = length();
            if (len == 0.0) {
                throw std::runtime_error("Cannot normalize zero-length vector");
            }
            return *this / len;
        }

        void normalize_in_place() {
            double len = length();
            if (len == 0.0) {
                throw std::runtime_error("Cannot normalize zero-length vector");
            }
            *this /= len;
        }
    };

    // Component-wise multiplication
    inline Vec3 operator*(const Vec3& a, const Vec3& b) {
        return Vec3{a.x * b.x, a.y * b.y, a.z * b.z};
    }
    
    
    // Dot product
    inline double dot(const Vec3& a, const Vec3& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    // Cross product
    inline Vec3 cross(const Vec3& a, const Vec3& b) {
        return Vec3{
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        };
    }

    // left scalar operations
    inline Vec3 operator*(double scalar, const Vec3& v) {
        return Vec3{v.x * scalar, v.y * scalar, v.z * scalar};
    }

    inline std::ostream& operator<<(std::ostream& os, const Vec3& v) {
        os << "Vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
}
