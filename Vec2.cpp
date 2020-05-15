#include "vec2.h"

Vec2::Vec2() :
    x(0.0f),
    y(0.0f) {
}

Vec2::Vec2(float x, float y) :
    x(x), y(y) {
}

float Vec2::squared_distance(const Vec2& v) const {
    return (x - v.x)*(x-v.x) + (y - v.y)*(y-v.y);
}

Vec2& Vec2::operator=(const Vec2& v) {
    x = v.x;
    y = v.y;
    return *this;
}

Vec2 Vec2::operator+(const Vec2& v) const {
    Vec2 u;
    u.x = x + v.x;
    u.y = y + v.y;
    return u;
}

Vec2 Vec2::operator-(const Vec2& v) const {
    Vec2 u;
    u.x = x - v.x;
    u.y = y - v.y;
    return u;
}

Vec2 Vec2::operator*(const float s) const {
    Vec2 u;
    u.x = s * x;
    u.y = s * y;
    return u;
}

float Vec2::dot(const Vec2& v) const {
    return x * v.x + y * v.y;
}

float Vec2::squared_norm() const {
    return x * x + y * y;
}