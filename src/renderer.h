#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include "map.h"
#include "mouse.h"

class Font;
class Mouse;

class Camera
{
public:
    Vector2f pos;
    Vector2i res;
};

extern YE_Map stmap;
extern Actor *playerpawn;
extern Player *player;
extern std::map<std::string, GLuint> Textures;
extern GLuint Lightbuffer;
extern Font *font;
extern Font *menufont;
extern Mouse *pmouse;
extern Camera *cam;
extern float deltatime;
void YE_Renderer(void);

#endif // RENDERER_H_INCLUDED
