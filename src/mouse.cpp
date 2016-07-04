#include "mouse.h"
#include "math.h"

#define SCALE_STEP 8.0

void Mouse::HandleEvents()
{
    switch(event.type)
    {
    case SDL_MOUSEMOTION:
        pos.x = event.motion.x;
        pos.y = screen_height - event.motion.y;
        break;
    case SDL_MOUSEWHEEL:
        if(event.wheel.y > 0)
            tile_size = clip(tile_size+SCALE_STEP, SCALE_MIN, SCALE_MAX);
        else
            tile_size = clip(tile_size-SCALE_STEP, SCALE_MIN, SCALE_MAX);
        break;
    }
}

void Cursor::Create(std::string image, float width, float height)
{
    Image = Textures[image];

    Width = width;
    Height = height;
}

void Cursor::Draw(Vector2f pos)
{
    glBindTexture(GL_TEXTURE_2D, Image);

    float CHalfWidth = Width/2;
    float CHalfHeight = Height/2;

    float x = pos.x + CHalfWidth;
    float y = pos.y - CHalfHeight;

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(x-CHalfWidth, y-CHalfHeight);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(x-CHalfWidth, y+CHalfHeight);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(x+CHalfWidth, y+CHalfHeight);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(x+CHalfWidth, y-CHalfHeight);
    glEnd();
}

Vector2f ScreenToWorld(Vector2f pos)
{
    Vector2f fpos = pos / tile_size;

    fpos.x += cam.x - half_width;
    fpos.y += cam.y - half_height;

    return fpos;
}

Vector2f WorldToScreen(Vector2f pos)
{
    Vector2f fpos = pos;

    fpos.x -= cam.x + half_width;
    fpos.y -= cam.y - half_height;

    fpos *= tile_size;
    return fpos;
}
