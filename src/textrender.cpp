#include "textrender.h"

#include "log.h"

static FT_Library ft;

static const char* ErrorString(FT_Error err)
{
    #undef __FTERRORS_H__
    #define FT_ERRORDEF( e, v, s )  case e: return s;
    #define FT_ERROR_START_LIST     switch (err) {
    #define FT_ERROR_END_LIST       }
    #include FT_ERRORS_H
    return "(Unknown error)";
}

void YE_InitTextRenderer()
{
    FT_Error error = FT_Init_FreeType(&ft);
    if (error)
    {
        Log(1, "[Text renderer] Failed to initialize FreeType text rendering library: %s", ErrorString(error));
        exit(1);
    }

    Log(0, "[Text renderer] FreeType initalized.");
}


FontFace::FontFace(const char *path)
{
    FT_Error error = FT_New_Face(ft, path, 0, &mFace);
    if (error)
    {
        Log(1, "[Text renderer] Failed to load %s: %s", path, ErrorString(error));
        mFontLoaded = false;
        return;
    }

    Log(0, "[Text renderer] Loaded font face %s", path);
    mFontLoaded = true;
}

FontFace::~FontFace()
{
    FT_Error error = FT_Done_Face(mFace);
    if (error)
        Log(1, "[Text renderer] Warning: failed to free font face: %s", ErrorString(error));
}

void FontFace::drawText(Vector2f position, const char *text, int size)
{

}

