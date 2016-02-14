#include "fontloader.h"

#include "font.h"
#include "log.h"

static FT_Library ft;

static const char* FTErrorString(FT_Error err)
{
    #undef __FTERRORS_H__
    #define FT_ERRORDEF( e, v, s )  case e: return s;
    #define FT_ERROR_START_LIST     switch (err) {
    #define FT_ERROR_END_LIST       }
    #include FT_ERRORS_H
    return "(Unknown error)";
}

void YE_InitFontLoader()
{
    FT_Error error = FT_Init_FreeType(&ft);
    if (error)
    {
        Log(1, "[Font loader] Failed to initialize FreeType font reader library: %s", FTErrorString(error));
        ft = nullptr;
        return;
    }

    Log(0, "[Font loader] FreeType initalized.");
}

static unique_ptr<Glyph> YE_DefaultGlyphForSize(int size)
{
    return make_unique<Glyph>(0, Vector2f(size), Vector2f(0), Vector2f(size + 1, 0));
}

unique_ptr<Font> YE_LoadFont(const char *filepath, int size)
{
    auto font = make_unique<Font>(YE_DefaultGlyphForSize(size));
    Log(0, "[Font loader] loaded font %s at size %d", filepath, size);
    return font;
}

