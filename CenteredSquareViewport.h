#ifndef __CENTEREDSQUAREVIEWPORT__
#define __CENTEREDSQUAREVIEWPORT__

#include "Viewport.h"
#include "Vec2.h"

class CenteredSquareViewport: public Viewport {
protected:
    int window_width,
        window_height,
        viewport_topleft_corner_x,
        viewport_topleft_corner_y,
        viewport_size;
public:
    CenteredSquareViewport(int initial_width, int initial_height, int initial_viewport_topleft_corner_x, int initial_viewport_topleft_corner_y, int initial_viewport_size);
    void update(int width, int height);
    Vec2 get_mouse_position(int x, int y) const;
};

#endif