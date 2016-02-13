#ifndef TILES_H_INCLUDED
#define TILES_H_INCLUDED

#include "common.h"

extern std::map<std::string, GLuint> Textures;

class Tile
{
public:
    Tile();

    void Draw(int x, int y);
    int Solid;
    char Texture[255];
};

bool YE_CheckTile(int x, int y);
void YE_DrawAO(int x, int y);
bool YE_CheckIfSolid(int x, int y);

#endif // TILES_H_INCLUDED
