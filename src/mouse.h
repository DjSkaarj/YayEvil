#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#include "common.h"
#include "geometry.h"
#include "renderer.h"

extern SDL_Event event;
extern int screen_width, screen_height;
extern float half_width, half_height;
extern Vector2f cam;

class Cursor
{
public:
    float Width, Height;
    GLuint Image;

    void Create(std::string image, float width, float height);
    void Draw(Vector2f pos);
};

class Mouse
{
public:
    Vector2f pos;

    Cursor* NormalCursor = new Cursor;
    void HandleEvents();
};

Vector2f ScreenToWorld(Vector2f pos);
Vector2f WorldToScreen(Vector2f pos);

#endif // MOUSE_H_INCLUDED
