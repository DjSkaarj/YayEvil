#ifndef TEXTURES_H_INCLUDED
#define TEXTURES_H_INCLUDED

#include "common.h"

extern bool YE_LogTex;
extern std::map<std::string, GLuint> Textures;

GLuint GetTexture(std::string name);
void YE_LoadTextures(void);
void YE_LoadTexturesDir(const char* dirpath);
GLuint YE_LoadImage(const char *filename);


#endif // TEXTURES_H_INCLUDED