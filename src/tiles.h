#ifndef TILES_H_INCLUDED
#define TILES_H_INCLUDED

#include "common.h"
#include "geometry.h"

extern std::map<std::string, GLuint> Textures;

class Tile
{
public:
    Tile();

    void Draw(Vector2i pos);
    int Solid;
    char Texture[255];
};

void YE_DrawAO(Vector2i pos);

#endif // TILES_H_INCLUDED
