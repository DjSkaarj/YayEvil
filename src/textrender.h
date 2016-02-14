#ifndef TEXTRENDER_H_INCLUDED
#define TEXTRENDER_H_INCLUDED

#include "common.h"
#include "geometry.h"

class CachedFont;

class FontFace
{
public:
    FontFace(const char *path);
    ~FontFace();

    void drawText(Vector2f position, const char *text, int size);

private:
    bool mFontLoaded;
    FT_Face mFace;

    std::unordered_map<int, unique_ptr<CachedFont>> mCachedFonts;
};

class CachedFont
{

};

void YE_InitFontRenderer();

#endif // TEXTRENDER_H_INCLUDED
