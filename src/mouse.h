#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

#include "common.h"
#include "geometry.h"
#include "renderer.h"

class Camera;

extern SDL_Event event;
extern float half_width, half_height;
extern Camera *cam;
extern float tile_size;

class Cursor
{
public:
    Vector2f Size;
    GLuint Image;

    void Create(std::string image, float width, float height);
    void Draw(Vector2f pos);
};

class Mouse
{
public:
    Vector2f pos;
    Mouse(Actor *input);

    Cursor* NormalCursor = new Cursor;
    void HandleEvents();
    float GetAngle();
private:
    Actor *player;
};

Vector2f ScreenToWorld(Vector2f pos);
Vector2f WorldToScreen(Vector2f pos);

#endif // MOUSE_H_INCLUDED
