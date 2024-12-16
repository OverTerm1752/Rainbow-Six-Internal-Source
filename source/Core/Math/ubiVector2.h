#pragma once

class ubiVector2 {
public:
    constexpr ubiVector2(float x = 0.f, float y = 0.f) noexcept
        : x(x), y(y) {}

    constexpr ubiVector2 operator-(const ubiVector2& other) const noexcept {
        return ubiVector2(x - other.x, y - other.y);
    }

    constexpr ubiVector2 operator+(const ubiVector2& other) const noexcept {
        return ubiVector2(x + other.x, y + other.y);
    }

    constexpr ubiVector2 operator/(float factor) const noexcept {
        return ubiVector2(x / factor, y / factor);
    }

    constexpr ubiVector2 operator*(float factor) const noexcept {
        return ubiVector2(x * factor, y * factor);
    }

    ubiVector2& operator+=(const ubiVector2& other) noexcept {
        x += other.x; y += other.y;
        return *this;
    }

    ubiVector2& operator-=(const ubiVector2& other) noexcept {
        x -= other.x; y -= other.y;
        return *this;
    }

    ubiVector2& operator*=(float factor) noexcept {
        x *= factor; y *= factor;
        return *this;
    }

    ubiVector2& operator/=(float factor) noexcept {
        x /= factor; y /= factor;
        return *this;
    }

    float x, y;
};
