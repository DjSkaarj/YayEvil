#include "mouse.h"

Mouse::Mouse() {}

void Mouse::HandleEvents()
{
    switch(event.type)
    {
    case SDL_MOUSEMOTION:
        pos.x = event.motion.x;
        pos.y = screen_height - event.motion.y;
    }
}

Vector2f ScreenToWorld(Vector2i pos)
{
    Vector2f fpos = pos / 64.0;

    fpos.x += cam_x - half_width;
    fpos.y += cam_y - half_height;

    return fpos;
}

Vector2f WorldToScreen(Vector2f pos)
{
    Vector2f fpos = pos;

    fpos.x -= cam_x + half_width;
    fpos.y -= cam_y - half_height;

    fpos *= 64.0;
    return fpos;
}
