#ifndef TILES_H_INCLUDED
#define TILES_H_INCLUDED

class Tile
{
public:
    Tile();

    void Draw(float x, float y);
    int Solid;
    char Texture[255];
};

#endif // TILES_H_INCLUDED
