#include "Paddle.h"
#include <limits>
#include <gl/glut.h>
#include <gl/gl.h>

Paddle::Paddle(float plane_height) {
    x_position = 0.0f;
    x_plane_height = plane_height;
    sides[0] = LineSegment(x_position - 0.25f, x_plane_height + 0.05f, x_position - 0.05f, x_plane_height - 0.05f);
    sides[1] = LineSegment(x_position - 0.25f, x_plane_height - 0.05f, x_position + 0.05f, x_plane_height - 0.05f);
    sides[2] = LineSegment(x_position + 0.25f, x_plane_height - 0.05f, x_position + 0.05f, x_plane_height + 0.05f);
    sides[3] = LineSegment(x_position + 0.25f, x_plane_height + 0.05f, x_position - 0.05f, x_plane_height + 0.05f);
}

void Paddle::update(float p) {
    x_position = p;
    sides[0] = LineSegment(x_position - 0.25f, x_plane_height + 0.05f, x_position - 0.25f, x_plane_height - 0.05f);
    sides[1] = LineSegment(x_position - 0.25f, x_plane_height - 0.05f, x_position + 0.25f, x_plane_height - 0.05f);
    sides[2] = LineSegment(x_position + 0.25f, x_plane_height - 0.05f, x_position + 0.25f, x_plane_height + 0.05f);
    sides[3] = LineSegment(x_position + 0.25f, x_plane_height + 0.05f, x_position - 0.25f, x_plane_height + 0.05f);
}

void Paddle::display() const {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(x_position - 0.25f, x_plane_height + 0.05f);
    glVertex2f(x_position - 0.25f, x_plane_height - 0.05f);
    glVertex2f(x_position + 0.25f, x_plane_height - 0.05f);
    glVertex2f(x_position + 0.25f, x_plane_height + 0.05f);
    glEnd();
}

float Paddle::squared_distance(const Vec2& v) const {
    float closest = std::numeric_limits<float>::max();
    for (int i = 0; i != 4; ++i) {
        float distance = sides[i].squared_distance(v);
        if (distance < closest)
            closest = distance;
    }
    return closest;
}

Vec2 Paddle::get_closest_point(const Vec2& v) const {
    float shortest_distance = std::numeric_limits<float>::max();
    int closest_object;
    for (int i = 0; i != 4; ++i) {
        float distance = sides[i].squared_distance(v);
        if (distance < shortest_distance) {
            shortest_distance = distance;
            closest_object = i;
        }
    }
    return sides[closest_object].get_closest_point(v);
}


Vec2 Paddle::get_normal_at_closest_point(const Vec2& v) const {
    float closest = std::numeric_limits<float>::max();
    int closest_side;
    for (int i = 0; i != 4; ++i) {
        float distance = sides[i].squared_distance(v);
        if (distance <= closest) {
            closest = distance;
            closest_side = i;
        }
    }
    return sides[closest_side].get_normal_at_closest_point(v);
}

Vec2 Paddle::get_velocity_at_point(const Vec2& collission_point) const {
    /*Add asseration that collission point is in object*/
    return Vec2(0.0f, 0.0f);
}

float Paddle::get_apparent_mass_at_point(const Vec2& collission_point) const {
    return std::numeric_limits<float>::max();
}