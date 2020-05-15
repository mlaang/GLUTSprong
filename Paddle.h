#ifndef __PADDLE__
#define __PADDLE__

#include "CollissionObject2D.h"
#include "LineSegment.h"

class Paddle: public CollissionObject2D {
protected:
    float x_position;
    LineSegment sides[4];
    float x_plane_height;
public:
    Paddle(float plane_height);
    void update(float p);
    void display() const;
    float squared_distance(const Vec2& v) const;
    Vec2 get_closest_point(const Vec2& v) const;
    Vec2 get_normal_at_closest_point(const Vec2& v) const;
    Vec2 get_velocity_at_point(const Vec2& collission_point) const;
    float get_apparent_mass_at_point(const Vec2& collission_point) const;
};

#endif