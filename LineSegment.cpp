#include "LineSegment.h"
#include <limits>
#include <math.h>

LineSegment::LineSegment() {
}

LineSegment::LineSegment(float x1, float y1, float x2, float y2) :
    start(x1, y1),
    end(x2, y2) {
}

float LineSegment::squared_distance(const Vec2& v) const {
    float scalar_projection = (v - start).dot(end - start) / start.squared_distance(end);
    if (scalar_projection > 1.0f) scalar_projection = 1.0f;
    else if (scalar_projection < 0.0f) scalar_projection = 0.0f;
    Vec2 projection = start + (end - start) * scalar_projection; //Projection of v onto the extended line.
    return v.squared_distance(projection);
}

Vec2 LineSegment::get_closest_point(const Vec2& v) const {
    float scalar_projection = (v - start).dot(end - start) / start.squared_distance(end);
    if (scalar_projection > 1.0f)
        return end;
    else if (scalar_projection < 0.0f)
        return start;
    else
        return start + (end - start) * scalar_projection;
}

Vec2 LineSegment::get_normal_at_closest_point(const Vec2& v) const {
    float scalar_projection = (v - start).dot(end - start) / start.squared_distance(end);
    if (scalar_projection > 1 || scalar_projection < 0)
        return Vec2(0.0f, 0.0f);
    else {
        Vec2 direction = (end - start) * (1.0f / sqrtf(start.squared_distance(end)));
        return Vec2(direction.y, -direction.x);
    }
}

Vec2 LineSegment::get_velocity_at_point(const Vec2& collission_point) const {
    /*Add asseration that collission point is in object*/
    return Vec2(0.0f, 0.0f);
}

float LineSegment::get_apparent_mass_at_point(const Vec2& collission_point) const {
    return std::numeric_limits<float>::max();
}