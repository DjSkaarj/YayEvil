#include "common.h"
#define GL_BGR 0x80E0
#define GL_BGRA 0x80E1

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
}

int YE_Index2D(int x, int y, int width)
{
    return x + (y * width);
}

void YE_LoadMap (const char* filename)
{
    FILE* level;

    Log(0, "[Map loader] Opening '%s'", filename);
    level = fopen(filename, "r");
    if(!level)
        Log(1, "[Map list] Couldn't open map file: '%s'!", filename);

    int width, height;
    YE_InitParser(level);
    YE_ReadString();
    width = YE_ReadInt();
    height = YE_ReadInt();
    stmap.Width = width;
    stmap.Height = height;
    Log(0, "[Map loader] Loaded map %s[%d,%d]", filename, width, height);

    stmap.Tiles = new Tile[width*height];
    for(int i=0; i<width*height; i++)
    {
        strcpy(stmap.Tiles[i].Texture, "none");
        stmap.Tiles[i].Solid = 0;
    }
    while(YE_NextLine())
    {
        char cmd[255];
        YE_ReadStringA(cmd, 255);

        /*if tile*/
        if(!strcmp(cmd, "tile"))
        {
            int x = YE_ReadInt();
            int y = YE_ReadInt();

            if(x < 0 || x >= stmap.Width || y < 0 || y >= stmap.Height)
                Log(0, "[Map loader] Tile at [%d,%d] is outside of map[%d,%d]!", x, y, stmap.Width, stmap.Height);
            else
            {
                int index = YE_Index2D(x, y, width);

                char texture[255];
                YE_ReadStringA(texture, 255);
                YE_StrToLower(texture);
                int solid = YE_ReadInt();

                strcpy(stmap.Tiles[index].Texture, texture);
                stmap.Tiles[index].Solid = solid;
                Log(0, "[Map loader] Registered new tile [%d,%d]: texture=%s solid=%d", x, y, texture, solid);
            }
        }

        else if(!strcmp(cmd, "actor"))
        {}

        else if(!strcmp(cmd, "light"))
        {
            Light lightbuff;
            lightbuff.X = YE_ReadFloat();
            lightbuff.Y = YE_ReadFloat();
            lightbuff.Radius = YE_ReadFloat();
            lightbuff.RColor = YE_ReadFloat();
            lightbuff.GColor = YE_ReadFloat();
            lightbuff.BColor = YE_ReadFloat();
            stmap.Lights.push_back(lightbuff);
            Log(0, "[Map loader] Registered new light [%f,%f]: radius=%f color=%f|%f|%f", lightbuff.X, lightbuff.Y, lightbuff.Radius, lightbuff.RColor, lightbuff.GColor, lightbuff.BColor);
        }

        else if(!strcmp(cmd, "globalcolor"))
        {
            stmap.Rcolor = std::min(1.0f, YE_ReadFloat());
            stmap.Gcolor = std::min(1.0f, YE_ReadFloat());
            stmap.Bcolor = std::min(1.0f, YE_ReadFloat());
            Log(0, "[Map loader] Set global color to: %f %f %f", stmap.Rcolor, stmap.Gcolor, stmap.Bcolor);
        }

        else if(!strcmp(cmd, "backgroundcolor"))
        {
            stmap.BGRcolor = std::min(1.0f, YE_ReadFloat());
            stmap.BGGcolor = std::min(1.0f, YE_ReadFloat());
            stmap.BGBcolor = std::min(1.0f, YE_ReadFloat());
            Log(0, "[Map loader] Set background color to: %f %f %f", stmap.BGRcolor, stmap.BGGcolor, stmap.BGBcolor);
        }

        else if(!strcmp(cmd, "ambientcolor"))
        {
            stmap.ARcolor = std::min(1.0f, YE_ReadFloat());
            stmap.AGcolor = std::min(1.0f, YE_ReadFloat());
            stmap.ABcolor = std::min(1.0f, YE_ReadFloat());
            Log(0, "[Map loader] Set ambient color to: %f %f %f", stmap.ARcolor, stmap.AGcolor, stmap.ABcolor);
        }

        else if(!strcmp(cmd, "#"))
        {}

        else Log(0, "[Warning] [Map loader] '%s' is invalid map command", cmd);
    }
    fclose(level);
    Log(0, "[Map loader] Reading '%s' is finished!", filename);
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
        gpuformat = GL_RGBA8; //GPUs don't like 24-bit colors

        if (rmask == 0x000000ff)
            origformat = GL_RGBA;
        else
            origformat = GL_BGRA;
        break;

    case 3:
        gpuformat = GL_RGBA8;

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

    // we should turn off mipmapping or OpenGL will use non-existent (white) mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, gpuformat, // second parameter: number of mipmap
                 image->w, image->h,
                 0, // <----------------------------------------- old useless crap
                 origformat, GL_UNSIGNED_BYTE, image->pixels);

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
        if((YE_EndsWith(file.name, "bmp")||YE_EndsWith(file.name, "png")||YE_EndsWith(file.name, "tga")||YE_EndsWith(file.name, "jpeg"))&&!file.is_dir)
        {
            char path[255];
            strcpy(path, dirpath);
            strcat(path, file.name);
            GLuint texbuffer = YE_LoadImage(path);
            if(texbuffer!=0)
            {
                char loadtex[255];
                strcpy(loadtex, file.name);
                YE_StrToLower(loadtex);
                Textures.insert(std::pair<std::string, GLuint>((loadtex), texbuffer));
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
    Log(0, "[Texture loader] Textures loaded!");
    Log(0, "[Texture loader] Loading sprites...");
    YE_LoadTexturesDir("textures/sprites/");
    Log(0, "[Texture loader] Loaded sprites!");
}
