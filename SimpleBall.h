#ifndef __SIMPLEBALL__
#define __SIMPLEBALL__

#include "Ball.h"
#include "Vec2.h"
#include "CollissionObject2D.h"

//#define COLLISSION_DEBUG
/* When COLLISSION_DEBUG is enabled several lines will be drawn, some on top of each other:
 *
 * 1. A white line showing the velocity vector multiplied by 0.5f,
 * 2. a red line from the centre of each ball to the nearest point on the nearest collission object,
 * 3. a green line at the nearest point of the nearest collission object showing the normal vector of the collission object at that point,
 * 4. two blue lines, corresponding to the component of the velocity 
 */

class SimpleBall: public CollissionObject2D {
protected:
    float radius;
    Vec2 position,
         velocity,
         postupdate_velocity;
    int closest_object;
#ifdef COLLISSION_DEBUG
    CollissionObject2D* closest_object_pointer;
#endif
public:
    SimpleBall();
    SimpleBall(float x, float y, float vx, float vy, float r);
    void display() const;
    void apply_free_motion(float time_elapsed);
    void preupdate(float time_elapsed, CollissionObject2D** collison_objects, int N);
    void update();
    void resolve_collissions(float time_elapsed, CollissionObject2D** collison_objects, int N);
    bool collissions_resolved(CollissionObject2D** collission_objects) const;
    float squared_distance(const Vec2& v) const;
    Vec2 get_closest_point(const Vec2& v) const;
    Vec2 get_normal_at_closest_point(const Vec2& v) const;
    Vec2 get_velocity_at_point(const Vec2& collission_point) const;
    float get_apparent_mass_at_point(const Vec2& collission_point) const;
    bool is_fully_outside(float left_limit, float right_limit, float bottom_limit, float top_limit) const;
};

#endif