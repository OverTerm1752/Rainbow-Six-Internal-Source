#pragma once

class ubiQuaternion {
public:
    constexpr ubiQuaternion(float w = 1.f, float x = 0.f, float y = 0.f, float z = 0.f) noexcept
        : w(w), x(x), y(y), z(z) {}

    constexpr ubiQuaternion operator+(const ubiQuaternion& other) const noexcept {
        return ubiQuaternion(w + other.w, x + other.x, y + other.y, z + other.z);
    }

    constexpr ubiQuaternion operator-(const ubiQuaternion& other) const noexcept {
        return ubiQuaternion(w - other.w, x - other.x, y - other.y, z - other.z);
    }

    constexpr ubiQuaternion operator*(float factor) const noexcept {
        return ubiQuaternion(w * factor, x * factor, y * factor, z * factor);
    }

    constexpr ubiQuaternion operator*(const ubiQuaternion& other) const noexcept {
        return ubiQuaternion(
            w * other.w - x * other.x - y * other.y - z * other.z,
            w * other.x + x * other.w + y * other.z - z * other.y,
            w * other.y - x * other.z + y * other.w + z * other.x,
            w * other.z + x * other.y - y * other.x + z * other.w
        );
    }

    ubiQuaternion& operator+=(const ubiQuaternion& other) noexcept {
        w += other.w; x += other.x; y += other.y; z += other.z;
        return *this;
    }

    ubiQuaternion& operator-=(const ubiQuaternion& other) noexcept {
        w -= other.w; x -= other.x; y -= other.y; z -= other.z;
        return *this;
    }

    ubiQuaternion& operator*=(float factor) noexcept {
        w *= factor; x *= factor; y *= factor; z *= factor;
        return *this;
    }

    ubiQuaternion& operator*=(const ubiQuaternion& other) noexcept {
        *this = *this * other;
        return *this;
    }

    float w, x, y, z; 
};
