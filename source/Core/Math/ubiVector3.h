#pragma once

class ubiVector3 {
public:
    constexpr ubiVector3(float x = 0.f, float y = 0.f, float z = 0.f) noexcept
        : x(x), y(y), z(z) {}

    constexpr ubiVector3 operator-(const ubiVector3& other) const noexcept {
        return ubiVector3(x - other.x, y - other.y, z - other.z);
    }

    constexpr ubiVector3 operator+(const ubiVector3& other) const noexcept {
        return ubiVector3(x + other.x, y + other.y, z + other.z);
    }

    constexpr ubiVector3 operator/(float factor) const noexcept {
        return ubiVector3(x / factor, y / factor, z / factor);
    }

    constexpr ubiVector3 operator*(float factor) const noexcept {
        return ubiVector3(x * factor, y * factor, z * factor);
    }

    ubiVector3& operator+=(const ubiVector3& other) noexcept {
        x += other.x; y += other.y; z += other.z;
        return *this;
    }

    ubiVector3& operator-=(const ubiVector3& other) noexcept {
        x -= other.x; y -= other.y; z -= other.z;
        return *this;
    }

    ubiVector3& operator*=(float factor) noexcept {
        x *= factor; y *= factor; z *= factor;
        return *this;
    }

    ubiVector3& operator/=(float factor) noexcept {
        x /= factor; y /= factor; z /= factor;
        return *this;
    }

    void Normalize() {
        float magnitude = sqrt(x * x + y * y + z * z);
        if (magnitude > 0.0f) {
            x /= magnitude;
            y /= magnitude;
            z /= magnitude;
        }
    }

    float x, y, z;
};
