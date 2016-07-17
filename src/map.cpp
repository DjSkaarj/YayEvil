#include "common.h"
#include "map.h"

#include "log.h"
#include "math.h"
#include "strings.h"
#include "states.h"

YE_Map::YE_Map()
{
    Rcolor = 1.0;
    Gcolor = 1.0;
    Bcolor = 1.0;

    BGRcolor = 0.0;
    BGGcolor = 0.0;
    BGBcolor = 0.0;

    ARcolor = 0.5;
    AGcolor = 0.5;
    ABcolor = 0.5;

    PlayerX = 0;
    PlayerY = 0;
}

int YE_Map::Index2d(Vector2i pos) const
{
    return pos.x + (pos.y * Size.x);
}

void YE_Map::TileDraw(Vector2i pos) const
{
    Tiles[Index2d(pos)].Draw(pos);
}

bool YE_Map::TileInMap(Vector2i pos) const
{
    return Rect().contains(pos);
}

bool YE_Map::TileExists(Vector2i pos) const
{
    if (!TileInMap(pos) || (!TileTexture(pos))) return false;

    return true;
}

bool YE_Map::TileIsSolid(Vector2i pos) const
{
    if (!TileExists(pos)) return true;

    return Tiles[Index2d(pos)].Solid;
}

GLuint YE_Map::TileTexture(Vector2i pos) const
{
    if (!TileInMap(pos)) return false;

    return Tiles[Index2d(pos)].Texture;
}

void YE_Map::SetTileSolid(Vector2i pos, bool x)
{
    if (!TileInMap(pos)) return;

    Tiles[Index2d(pos)].Solid = x;
}

void YE_Map::SetTileTexture(Vector2i pos, GLuint x)
{
    if (!TileInMap(pos)) return;

    Tiles[Index2d(pos)].Texture = x;
}

void YE_LoadMap (const char *filename)
{
    FILE* level;

    Log(0, "[Map loader] Opening '%s'...", filename);
    level = fopen(filename, "r");
    if(!level)
        Log(1, "[Map loader] Couldn't open map file: '%s'!", filename);

    int width, height;

    YE_InitParser(level);
    YE_ReadString();
    width = YE_ReadInt();
    height = YE_ReadInt();

    stmap.Size = Vector2i(width, height);
    Log(0, "[Map loader] Parsing map '%s' [%d,%d]...", filename, width, height);

    stmap.Tiles = new Tile[width*height];

    while(YE_NextLine())
    {
        char cmd[255];
        YE_ReadStringA(cmd, 255);

        if(!strcmp(cmd, "tile"))
        {
            int x = YE_ReadInt();
            int y = YE_ReadInt();

            Vector2i vec = Vector2i(x, y);

            if(!stmap.TileInMap(vec))
                Log(0, "[Map loader] Tile at [%d,%d] is outside of map[%d,%d]!", x, y, stmap.Size.x, stmap.Size.y);
            else
            {
                char texture[255];
                YE_ReadStringA(texture, 255);
                YE_StrToLower(texture);
				std::string s = texture;
				s.erase(s.end() - 4, s.end());

                int solid = YE_ReadInt();

                stmap.SetTileSolid(vec, solid);
                stmap.SetTileTexture(vec, Textures[s]);

                if(YE_LogMap)
                    Log(0, "[Map loader] Registered new tile [%d,%d]: texture=%s solid=%d", x, y, texture, solid);
            }
        }

        else if(!strcmp(cmd, "actor"))
        {
            float x = YE_ReadFloat();
            float y = YE_ReadFloat();
			char name[255];
			YE_ReadStringA(name, 255);

            Actor actorbuff(Vector2f(x, y));
			if (ActorTypes.find(name) == ActorTypes.end())
			{
				Log(0, "[Warning] [Map loader] Actor name '%s' isn't presented in YE! Skipping actor...");
				break;
			}
			actorbuff.CurrentState = ActorTypes[name]->Clone();
			actorbuff.SetName(name);
            stmap.Actors.push_back(actorbuff);
        }

        else if(!strcmp(cmd, "light"))
        {
            Light lightbuff;
            lightbuff.pos.x = YE_ReadFloat();
            lightbuff.pos.y = YE_ReadFloat();

            lightbuff.Radius = YE_ReadFloat();
            lightbuff.RColor = YE_ReadFloat();
            lightbuff.GColor = YE_ReadFloat();
            lightbuff.BColor = YE_ReadFloat();
            stmap.Lights.push_back(lightbuff);
            if(YE_LogMap)
                Log(0, "[Map loader] Registered new light [%f,%f]: radius=%f color=%f|%f|%f", lightbuff.pos.x, lightbuff.pos.y, lightbuff.Radius, lightbuff.RColor, lightbuff.GColor, lightbuff.BColor);
        }

        else if(!strcmp(cmd, "globalcolor"))
        {
            stmap.Rcolor = std::min(1.0f, YE_ReadFloat());
            stmap.Gcolor = std::min(1.0f, YE_ReadFloat());
            stmap.Bcolor = std::min(1.0f, YE_ReadFloat());
            if(YE_LogMap)
                Log(0, "[Map loader] Set global color to: %f %f %f", stmap.Rcolor, stmap.Gcolor, stmap.Bcolor);
        }

        else if(!strcmp(cmd, "backgroundcolor"))
        {
            stmap.BGRcolor = std::min(1.0f, YE_ReadFloat());
            stmap.BGGcolor = std::min(1.0f, YE_ReadFloat());
            stmap.BGBcolor = std::min(1.0f, YE_ReadFloat());
            if(YE_LogMap)
                Log(0, "[Map loader] Set background color to: %f %f %f", stmap.BGRcolor, stmap.BGGcolor, stmap.BGBcolor);
        }

        else if(!strcmp(cmd, "ambientcolor"))
        {
            stmap.ARcolor = std::min(1.0f, YE_ReadFloat());
            stmap.AGcolor = std::min(1.0f, YE_ReadFloat());
            stmap.ABcolor = std::min(1.0f, YE_ReadFloat());
            if(YE_LogMap)
                Log(0, "[Map loader] Set ambient color to: %f %f %f", stmap.ARcolor, stmap.AGcolor, stmap.ABcolor);
        }

        else if(!strcmp(cmd, "playerstart"))
        {
            stmap.PlayerX = clip(YE_ReadFloat(), 0.0f, (float)stmap.Size.x);
            stmap.PlayerY = clip(YE_ReadFloat(), 0.0f, (float)stmap.Size.y);
            if(YE_LogMap)
                Log(0, "[Map loader] Player spawn: %f %f", stmap.PlayerX, stmap.PlayerY);
        }

        else if(!strcmp(cmd, "#"))
        {}

        else Log(0, "[Warning] [Map loader] '%s' is invalid map command! Skipping command...", cmd);
    }
    fclose(level);
    Log(0, "[Map loader] Finished parsing '%s'!", filename);
}

GLuint YE_LoadImage(const char *filename)
{
    SDL_Surface *image = IMG_Load(filename);
    if (image == NULL)
    {
        Log(1, "[YE_LoadImage] Failed to load %s: %s", filename, SDL_GetError());
        return 0;
    }

    GLenum origformat;
    GLenum gpuformat;

    int bpp   = image->format->BytesPerPixel;
    int rmask = image->format->Rmask;

    switch (bpp)
    {
    case 4:
        gpuformat = GL_RGBA8;

        if (rmask == 0x000000ff)
            origformat = GL_RGBA;
        else
            origformat = GL_BGRA;
        break;

    case 3:
        gpuformat = GL_RGBA8; // GPUs don't like 24-bit colors

        if (rmask == 0x000000ff)
            origformat = GL_RGB;
        else
            origformat = GL_BGR;
        break;

    case 1:
        gpuformat = GL_LUMINANCE8;
        origformat = GL_LUMINANCE;
        break;

    default:
        Log(1, "[YE_LoadImage] %s: unsupported image format", filename);
        SDL_FreeSurface(image);
        return 0;
    }

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

    glTexImage2D(GL_TEXTURE_2D, 0, gpuformat, image->w, image->h, 0, origformat, GL_UNSIGNED_BYTE, image->pixels);

    SDL_FreeSurface(image);
    return texture;
}

void YE_LoadTexturesDir(const char* dirpath)
{
    tinydir_dir dir;
    tinydir_file file;
    tinydir_open_sorted(&dir, dirpath);
    for (unsigned int i = 0; i < dir.n_files; i++)
    {
        tinydir_readfile_n(&dir, &file, i);
        if((YE_EndsWith(file.name, "bmp") || YE_EndsWith(file.name, "png") || YE_EndsWith(file.name, "tiff") || YE_EndsWith(file.name, "jpeg")) && !file.is_dir)
        {
            char path[255];
            strcpy(path, dirpath);
            strcat(path, file.name);
            GLuint texbuffer = YE_LoadImage(path);

            if(texbuffer != 0)
            {
                char loadtex[255];
                strcpy(loadtex, file.name);
                YE_StrToLower(loadtex);
				std::string s = loadtex;
				s.erase(s.end() - 4, s.end());
                Textures.insert(std::pair<std::string, GLuint>(s, texbuffer));
                if(YE_LogTex)
                    Log(0, "[Texture loader] Loaded texture %s", file.name);
            }
        }
    }
    tinydir_close(&dir);
}

void YE_LoadTextures(void)
{
    Log(0, "[Texture loader] Loading textures...");
    YE_LoadTexturesDir("textures/");
    Log(0, "[Texture loader] Finished loading textures!");

    Log(0, "[Texture loader] Loading sprites...");
    YE_LoadTexturesDir("textures/sprites/");
    Log(0, "[Texture loader] Finished loading sprites!");
}
