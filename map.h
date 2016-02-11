#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

class YE_Map
{
 public:
     YE_Map();
     char* Name;
     int Width, Height;
     float Rcolor, Gcolor, Bcolor, BGRcolor, BGGcolor, BGBcolor, ARcolor, AGcolor, ABcolor;
     Tile* Tiles;
     std::vector<Actor*> Actors;
     std::vector<Light> Lights;
};

extern YE_Map stmap;
extern std::map<std::string, GLuint> Textures;
extern std::vector<std::string> Maplist;
int YE_Index2D(int x, int y, int width);
void YE_LoadMap(const char* file);
void YE_LoadTextures(void);
GLuint YE_LoadImage(const char *filename);

#endif // MAP_H_INCLUDED
