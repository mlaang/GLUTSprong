#ifndef __COLLISSIONOBJECT2D__
#define __COLLISSIONOBJECT2D__

#include "Vec2.h"

class CollissionObject2D {
public:
    virtual float squared_distance(const Vec2& v) const = 0;
    virtual Vec2 get_closest_point(const Vec2& v) const = 0; //It is assumed that the vector is close to the object, so that the set of closest points can be seen as one point
    virtual Vec2 get_normal_at_closest_point(const Vec2& v) const = 0; //When the normal is undefined a vector of length zero is to be returned
    virtual Vec2 get_velocity_at_point(const Vec2& collission_point) const = 0;
    virtual float get_apparent_mass_at_point(const Vec2& collission_point) const = 0;
};

#endif