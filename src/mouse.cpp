#include "mouse.h"
#include "math.h"

void Mouse::HandleEvents()
{
    switch(event.type)
    {
    case SDL_MOUSEMOTION:
        pos.x = event.motion.x;
        pos.y = cam->res.y - event.motion.y;
        break;

    case SDL_MOUSEWHEEL:
        if(event.wheel.y > 0)
            tile_size = clip(tile_size+SCALE_STEP, SCALE_MIN, SCALE_MAX);
        else
            tile_size = clip(tile_size-SCALE_STEP, SCALE_MIN, SCALE_MAX);
        break;
    }
}

float Mouse::GetAngle()
{
    Vector2f worldpos = ScreenToWorld(pos);
    return atan2(worldpos.y - player->GetActor()->pos().y, worldpos.x - player->GetActor()->pos().x);
}

void Cursor::Create(std::string image, float width, float height)
{
    Image = Textures[image];

    Size = Vector2f(width, height);
}

void Cursor::Draw(Vector2f pos)
{
    glBindTexture(GL_TEXTURE_2D, Image);

    float CHalfWidth = Size.x/2;
    float CHalfHeight = Size.y/2;

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

    fpos.x += cam->pos.x - half_width;
    fpos.y += cam->pos.y - half_height;

    return fpos;
}

Vector2f WorldToScreen(Vector2f pos)
{
    Vector2f fpos = pos;

    fpos.x -= cam->pos.x + half_width;
    fpos.y -= cam->pos.y - half_height;

    fpos *= tile_size;
    return fpos;
}
