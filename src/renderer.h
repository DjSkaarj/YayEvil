#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include "map.h"
#include "mouse.h"

class Font;
class Mouse;

extern Vector2f cam;
extern int screen_width, screen_height;
extern YE_Map stmap;
extern Actor *player;
extern std::map<std::string, GLuint> Textures;
extern GLuint Lightbuffer;
extern Font *font;
extern Font *menufont;
extern Mouse *pmouse;
extern float deltatime;
void YE_Renderer(void);

#endif // RENDERER_H_INCLUDED
