#ifndef FONTLOADER_H_INCLUDED
#define FONTLOADER_H_INCLUDED

#include "common.h"

class Font;

void YE_InitFontLoader();
unique_ptr<Font> YE_LoadFont(const char *filepath, int size);

#endif // FONTLOADER_H_INCLUDED
