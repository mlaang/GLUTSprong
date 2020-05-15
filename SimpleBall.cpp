#include "SimpleBall.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <limits>
#include <assert.h>

#define SQR(x) ((x)*(x))

SimpleBall::SimpleBall():
    position(),
    velocity(),
    radius(0.1f) {
#ifdef COLLISSION_DEBUG
    closest_object_pointer = NULL;
#endif
}

SimpleBall::SimpleBall(float x, float y, float vx, float vy, float r) :
    position(x, y),
    velocity(vx, vy),
    radius(r) {
#ifdef  COLLISSION_DEBUG
    closest_object_pointer = NULL;
#endif
}

void SimpleBall::display() const {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    for (float theta = 0.0f; theta < 2 * M_PI; theta += 0.1f) {
        glVertex2f(position.x, position.y);
        glVertex2f(position.x + radius * cosf(theta), position.y + radius * sinf(theta));
        glVertex2f(position.x + radius * cosf(theta + 0.1f), position.y + radius * sinf(theta + 0.1f));
    }
    glEnd();
#ifdef COLLISSION_DEBUG
    glBegin(GL_LINES);
    glVertex2f(position.x, position.y);
    glVertex2f(0.5f * velocity.x + position.x, 0.5f * velocity.y + position.y);
    glEnd();
    if (closest_object_pointer) {
        Vec2 most_relevant_normal = closest_object_pointer->get_normal_at_closest_point(position);
        Vec2 most_relevant_point = closest_object_pointer->get_closest_point(position);
        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_LINES);
        glVertex2f(position.x, position.y);
        glVertex2f(most_relevant_point.x, most_relevant_point.y);
        glEnd();
        glColor3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_LINES);
        glVertex2f(most_relevant_point.x, most_relevant_point.y);
        glVertex2f(most_relevant_point.x + most_relevant_normal.x*0.25f, most_relevant_point.y + most_relevant_normal.y*0.25f);
        glEnd();
    }
#endif
}

void SimpleBall::apply_free_motion(float time_elapsed) {
    position = position + velocity * time_elapsed;
    postupdate_velocity = velocity;
}

void SimpleBall::preupdate(float time_elapsed, CollissionObject2D** collission_objects, int N) /* Time in ms. */ {
    float lowest_squared_distance = std::numeric_limits<float>::max();
    //This goes through the objects with which we might collide, originally this ball as well.
    //Because the distance to this ball is the distance to the surface of this ball and because
    //that is never *less* than the radius this object, if it were included, as it originally was, would never be able to meet the collission
    //condition, i.e. being at a distance to the center of this ball that is smaller than the radius.
    for (int i = 0; i != N; ++i) {
        float squared_distance = collission_objects[i]->squared_distance(position);
        if (squared_distance < lowest_squared_distance && collission_objects[i] != this) {
            lowest_squared_distance = squared_distance;
            closest_object = i;
        }
    }
#ifdef COLLISSION_DEBUG
    closest_object_pointer = collission_objects[closest_object];
#endif
    if (lowest_squared_distance < SQR(radius)) {
        Vec2 assumed_collission_point = collission_objects[closest_object]->get_closest_point(position);
        Vec2 velocity_of_collission_point_on_other_object = collission_objects[closest_object]->get_velocity_at_point(assumed_collission_point);
        float contact_point_mass = collission_objects[closest_object]->get_apparent_mass_at_point(assumed_collission_point);
        Vec2 normal = collission_objects[closest_object]->get_normal_at_closest_point(position);

        //If the normal returned is not a normal and instead the zero vector the normal is assumed to be
        //the movement vector. This will make corners work out in a reasonable way.
        if (normal.x == 0.0f && normal.y == 0.0f)
            normal = velocity * (1.0f / sqrtf(velocity.squared_norm()));

        //Normal component of own velocity and of the contact point velocity.
        Vec2 normal_component = normal * velocity.dot(normal);
        Vec2 contact_point_normal_component = normal * velocity_of_collission_point_on_other_object.dot(normal);

        //We construct the velocity of the frame in which the total momentum of the balls along the normal is zero.
        Vec2 velocity_of_frame_in_which_total_momentum_is_zero = (normal_component + contact_point_normal_component * contact_point_mass) * (1.0f/(1.0f + contact_point_mass));
        
        //The part of the velocity that is not along the normal is unaffected in the collission. We call this the remainder.
        Vec2 remainder = velocity - normal_component;
        //In the frame with net momentum zero conservation of momentum and velocity requires that
        //the velocities of two colliding objects are either unchanged or that the velocity of the
        //moving objects, from the point of view of the observer in the frame in which momentum is zero, that
        //the velocities are negated. The velocity that is negated is normal_component - velocity_of_frame_in_which_total_momentum_is_zero.
        //After being negated this is added to velocity_of_frame_in_which_total_momentum_is_zero to and to the part of the velocity which is
        //not involved in the collission.
        postupdate_velocity = remainder + velocity_of_frame_in_which_total_momentum_is_zero * 2.0f - normal_component;
    }
}

void SimpleBall::update() {
    velocity = postupdate_velocity;
}

bool SimpleBall::collissions_resolved(CollissionObject2D** collission_objects) const {
    return collission_objects[closest_object]->squared_distance(position) >= SQR(radius);
}

void SimpleBall::resolve_collissions(float time_elapsed, CollissionObject2D** collission_objects, int N) /* Time in ms. */ {
    if (collission_objects[closest_object]->squared_distance(position) < SQR(radius))
        position = position + velocity * time_elapsed;
}

float SimpleBall::squared_distance(const Vec2& v) const {
    return SQR(sqrtf(v.squared_distance(position)) - radius);
}

Vec2 SimpleBall::get_closest_point(const Vec2& v) const {
    Vec2 vector_from_centre_to_v = v - position;
    vector_from_centre_to_v = vector_from_centre_to_v * (1.0f/sqrtf(vector_from_centre_to_v.squared_norm())); //Had not implemented scalar division in Vec2, so multiplication with reciprocal is used.
    return position + vector_from_centre_to_v * radius;
}

Vec2 SimpleBall::get_normal_at_closest_point(const Vec2& v) const {
    return (v - position) * (1.0f/sqrtf(v.squared_distance(position)));
}

Vec2 SimpleBall::get_velocity_at_point(const Vec2& collission_point) const {
    /*We will not verify that the collission point is inside the object, as the collission point assumed by the calling object may be wrong.*/
    return velocity;
}

float SimpleBall::get_apparent_mass_at_point(const Vec2& collission_point) const {
    return 1.0f;
}

/*float SimpleBall::get_absorbed_momentum(const Vec2& collission_point, const Vec2& ingoing_momentum) const {
    Vec2 ray_from_collission_point_to_centre = position - collission_point;
    ray_from_collission_point_to_centre = ray_from_collission_point_to_centre * (1 / sqrtf(ray_from_collission_point_to_centre.squared_norm()));
    float incoming_momentum_component_though_centre = ingoing_momentum.dot(ray_from_collission_point_to_centre);
    float own_momentum_component_through_centre = velocity.dot(ray_from_collission_point_to_centre * -1.0f);
    //Now we need to use conservation of momentum and energy to calculate how much this ball absorbs from the collission
    //however, the actual absorption doesn't happen happen here, but instead the relevant update function, which updates each object
    //appropriately, taking into account what is absorbed by and from other objects using calls to this function and the corresponding
    //function in other objects.
    return 0.0f;
}*/

bool SimpleBall::is_fully_outside(float left_limit, float right_limit, float bottom_limit, float top_limit) const {
    return (position.x + radius < left_limit) || (right_limit < position.x - radius) ||
        (position.y + radius < bottom_limit) || (position.y - radius > top_limit);
}