#ifndef __VEC2__
#define __VEC2__

class Vec2 {
public:
    float x, y;
    Vec2();
    Vec2(float x, float y);
    float squared_distance(const Vec2& v) const;
    Vec2& operator=(const Vec2& v);
    Vec2 operator+(const Vec2& v) const;
    Vec2 operator-(const Vec2& v) const;
    Vec2 operator*(const float s) const;
    float dot(const Vec2& v) const;
    float squared_norm() const;
};

#endif