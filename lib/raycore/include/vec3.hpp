#pragma once

#include <ostream>
#include <cmath>

namespace raycore {
    struct vec3 {
        double x, y, z;

        vec3() : x(0), y(0), z(0) {}
        vec3(double x, double y, double z) : x(x), y(y), z(z) {}

        // Binary operations
        vec3 operator+(const vec3& other) const {
            return vec3{x + other.x, y + other.y, z + other.z};
        }

        vec3 operator-(const vec3& other) const {
            return vec3{x - other.x, y - other.y, z - other.z};
        }

        // unary operations
        vec3 operator-() const {
            return vec3{-x, -y, -z};
        }

        // Scalar operations
        vec3 operator*(double scalar) const {
            return vec3{x * scalar, y * scalar, z * scalar};
        }

        vec3 operator/(double scalar) const {

            // prevent division by zero
            if (scalar == 0.0f) {
                throw std::runtime_error("Division by zero in vec3");
            }

            return vec3{x / scalar, y / scalar, z / scalar};
        }

        // +=, -=, *=, /=
        vec3& operator+=(const vec3& other) {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        vec3& operator-=(const vec3& other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        vec3& operator*=(double scalar) {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        vec3& operator/=(double scalar) {
            // prevent division by zero
            if (scalar == 0.0f) {
                throw vec3{0.0f, 0.0f, 0.0f};
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

        vec3 normalize() const {
            double len = length();
            if (len == 0.0f) {
                throw std::runtime_error("Division by zero in vec3");
            }
            return *this / len;
        }

        void normalize_in_place() {
            double len = length();
            if (len == 0.0f) {
                throw std::runtime_error("Division by zero in vec3");
            }
            *this /= len;
        }
    };
}

// Dot product
inline double dot(const raycore::vec3& a, const raycore::vec3& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Cross product
inline raycore::vec3 cross(const raycore::vec3& a, const raycore::vec3& b) {
    return raycore::vec3{
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

// left scalar operations
inline raycore::vec3 operator*(double scalar, const raycore::vec3& v) {
    return raycore::vec3{v.x * scalar, v.y * scalar, v.z * scalar};
}


inline std::ostream& operator<<(std::ostream& os, const raycore::vec3& v) {
    os << "vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}
