#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "actors.h"
#include "geometry.h"
#include "tiles.h"
#include "states.h"

extern std::map<std::string, State*> ActorTypes;

class YE_Map
{
 public:
     YE_Map();
     int Index2d(Vector2i pos) const;
     void TileDraw(Vector2i pos) const;
     bool TileInMap(Vector2i pos) const;
     bool TileExists(Vector2i pos) const;

     bool TileIsSolid(Vector2i pos) const;
     GLuint TileTexture(Vector2i pos) const;
     void SetTileSolid(Vector2i pos, bool x);
     void SetTileTexture(Vector2i pos, GLuint x);

     Vector2i Size;
     Tile *Tiles;
     std::vector<Actor> Actors;
     std::vector<Light> Lights;
     std::string Name;

     float Rcolor, Gcolor, Bcolor, BGRcolor, BGGcolor, BGBcolor, ARcolor, AGcolor, ABcolor;
     float PlayerX, PlayerY;

     RectI Rect() const { return RectI(Size.x, Size.y); }
};

extern YE_Map stmap;

extern bool YE_LogMap;
extern bool YE_LogTex;

extern std::map<std::string, GLuint> Textures;
extern std::vector<std::string> Maplist;

void YE_LoadMap(const char *file);
void YE_ParseLine();
void YE_LoadTextures(void);
GLuint YE_LoadImage(const char *filename);

#endif // MAP_H_INCLUDED
