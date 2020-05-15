#ifndef __LINESEGMENT__
#define __LINESEGMENT__

#include "CollissionObject2D.h"

class LineSegment : public CollissionObject2D {
protected:
    Vec2 start,
         end;
public:
    LineSegment();
    LineSegment(float x1, float y1, float x2, float y2);
    float squared_distance(const Vec2& v) const;
    Vec2 get_closest_point(const Vec2& v) const;
    Vec2 get_normal_at_closest_point(const Vec2& v) const; //When the normal is undefined a vector of length zero is to be returned
    Vec2 get_velocity_at_point(const Vec2& collission_point) const;
    float get_apparent_mass_at_point(const Vec2& collission_point) const;
};

#endif