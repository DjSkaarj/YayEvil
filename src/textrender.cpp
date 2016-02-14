#include "textrender.h"

#include "log.h"

static FT_Library ft;

void YE_InitTextRenderer()
{
    FT_Error error = FT_Init_FreeType(&ft);
    if (error)
    {
        Log(1, "[Text renderer] Failed to initialize FreeType text rendering library: error code %d", error);
        exit(1);
    }

    Log(0, "[Text renderer] FreeType initalized.");
}


FontFace::FontFace(const char *path)
{
    FT_Error error = FT_New_Face(ft, "FreeSans.ttf", 0, &mFace);
    if (error)
    {
        Log(1, "[Text renderer] Failed to load %s: error code %d", path, error);
        mFontLoaded = false;
        return;
    }

    Log(0, "[Text renderer] Loaded font face %s", path);
    mFontLoaded = true;
}

