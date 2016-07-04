#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "actors.h"
#include "geometry.h"
#include "tiles.h"

class YE_Map
{
 public:
     YE_Map();
     int Index2d(Vector2i pos);
     bool CheckTile(Vector2i pos);
     bool TileIsSolid(Vector2i pos);

     Vector2i Size;
     Tile* Tiles;
     std::vector<Actor*> Actors;
     std::vector<Light> Lights;
     std::string Name;

     float Rcolor, Gcolor, Bcolor, BGRcolor, BGGcolor, BGBcolor, ARcolor, AGcolor, ABcolor;
     float PlayerX, PlayerY;

     RectI Rect() { return RectI(Size.x, Size.y); }
};

extern YE_Map stmap;

extern bool YE_LogMap;
extern bool YE_LogTex;

extern std::map<std::string, GLuint> Textures;
extern std::vector<std::string> Maplist;

void YE_LoadMap(const char* file);
void YE_LoadTextures(void);
GLuint YE_LoadImage(const char *filename);

#endif // MAP_H_INCLUDED
