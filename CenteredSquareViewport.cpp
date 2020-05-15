#include "CenteredSquareViewport.h"
#include <gl/glut.h>
#include <gl/gl.h>

CenteredSquareViewport::CenteredSquareViewport(int initial_width, int initial_height,
											   int initial_viewport_topleft_corner_x, int initial_viewport_topleft_corner_y,
											   int initial_viewport_size):
    window_width(initial_width),
    window_height(initial_height),
    viewport_topleft_corner_x(initial_viewport_topleft_corner_x),
    viewport_topleft_corner_y(initial_viewport_topleft_corner_y),
    viewport_size(initial_viewport_size) {
}

void CenteredSquareViewport::update(int width, int height) {
    window_width = width;
    window_height = height;
    viewport_size = width < height ? width : height;
    viewport_topleft_corner_x = width < height ? 0 : (width - height) / 2;
    viewport_topleft_corner_y = width < height ? (height - width) / 2 : 0;
    viewport_size = width < height ? width : height;
    glViewport(viewport_topleft_corner_x, viewport_topleft_corner_y, viewport_size, viewport_size);
}

Vec2 CenteredSquareViewport::get_mouse_position(int x, int y) const {
    Vec2 mouse_position;
    //y is shortest distance from the top of the window to the current mouse position,
    //thus it is increasing y leads to decreasing mouse_position_y in the OpenGL coordinates.
    mouse_position.x = (float)(x - viewport_topleft_corner_x) / (float)viewport_size;
    mouse_position.y = (float)(y - viewport_topleft_corner_y) / (float)viewport_size;
    mouse_position.x = 2.0f * (mouse_position.x - 0.5f);
    mouse_position.y = -2.0f * (mouse_position.y - 0.5f);
    return mouse_position;
}