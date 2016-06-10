#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED

#include "map.h"

class Font;

extern float cam_x, cam_y;
extern int screen_width, screen_height;
extern YE_Map stmap;
extern Actor *player;
extern std::map<std::string, GLuint> Textures;
extern GLuint Lightbuffer;
extern Font *font;
void YE_Renderer(void);

#endif // RENDERER_H_INCLUDED
