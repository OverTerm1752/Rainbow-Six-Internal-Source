#pragma once

class ubiVector4 {
public:
    constexpr ubiVector4(float x = 0.f, float y = 0.f, float z = 0.f, float w = 0.f) noexcept
        : x(x), y(y), z(z), w(w) {}

    constexpr ubiVector4 operator-(const ubiVector4& other) const noexcept {
        return ubiVector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    constexpr ubiVector4 operator+(const ubiVector4& other) const noexcept {
        return ubiVector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    constexpr ubiVector4 operator/(float factor) const noexcept {
        return ubiVector4(x / factor, y / factor, z / factor, w / factor);
    }

    constexpr ubiVector4 operator*(float factor) const noexcept {
        return ubiVector4(x * factor, y * factor, z * factor, w * factor);
    }

    ubiVector4& operator+=(const ubiVector4& other) noexcept {
        x += other.x; y += other.y; z += other.z; w += other.w;
        return *this;
    }

    ubiVector4& operator-=(const ubiVector4& other) noexcept {
        x -= other.x; y -= other.y; z -= other.z; w -= other.w;
        return *this;
    }

    ubiVector4& operator*=(float factor) noexcept {
        x *= factor; y *= factor; z *= factor; w *= factor;
        return *this;
    }

    ubiVector4& operator/=(float factor) noexcept {
        x /= factor; y /= factor; z /= factor; w /= factor;
        return *this;
    }

    float x, y, z, w;
};
