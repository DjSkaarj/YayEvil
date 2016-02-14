#include "textrender.h"

#include "log.h"

static FT_Library ft;

void YE_InitFontRenderer()
{
    FT_Error error = FT_Init_FreeType(&ft);
    if (error)
    {
        Log(1, "[TextRender] Failed to initialize FreeType text rendering library: error code %d", error);
        exit(1);
    }
}


FontFace::FontFace(const char *path)
{
    FT_Error error = FT_New_Face(ft, "FreeSans.ttf", 0, &mFace);
    if (error)
    {
        Log(1, "[TextRender] Failed to load %s: error code %d", path, error);
        mFontLoaded = false;
    }

    mFontLoaded = true;
}

