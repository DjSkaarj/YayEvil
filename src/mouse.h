#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#include "common.h"
#include "geometry.h"
#include "renderer.h"

extern SDL_Event event;
extern int screen_width, screen_height;
extern float half_width, half_height;
extern float cam_x, cam_y;

class Mouse
{
public:
    Vector2i pos;

    Mouse();
    void HandleEvents();
};

Vector2f ScreenToWorld(Vector2i pos);

#endif // MOUSE_H_INCLUDED
