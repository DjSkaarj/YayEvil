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
    return make_unique<Glyph>(0, Vector2i(size), Vector2f(0), Vector2f(size + 1, 0));
}

static void YE_LoadGlyph(Font *font, FT_Face face, char c)
{
    FT_Error error = FT_Load_Char(face, c, FT_LOAD_RENDER);
    if (error)
    {
        Log(1, "[Font loader] Failed to load glyph \"%c\": %s", c, FTErrorString(error));
        return;
    }

    FT_GlyphSlot glyph = face->glyph;

    auto size = Vector2i(glyph->bitmap.width, glyph->bitmap.rows);
    auto offset = Vector2f(glyph->bitmap_left, glyph->bitmap_top);
    auto advance = Vector2f(glyph->advance.x>>6, glyph->advance.y>>6);

    GLuint texture;
    GLenum origformat = GL_LUMINANCE;
    GLenum gpuformat = GL_LUMINANCE8;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Turn off mipmaps and enable linear interpolation
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, gpuformat,
                 size.x, size.y,
                 0, // <----------------------------------------- old useless crap
                 origformat, GL_UNSIGNED_BYTE, glyph->bitmap.buffer);

    font->SetGlyph(c, make_unique<Glyph>(texture, size, offset, advance));
}

unique_ptr<Font> YE_LoadFont(const char *filepath, int size)
{
    // Create font.
    auto font = make_unique<Font>(YE_DefaultGlyphForSize(size));

    // Open in FreeType.
    FT_Face face;
    FT_Error error = FT_New_Face(ft, filepath, 0, &face);
    if (error)
    {
        Log(1, "[Font loader] Failed to load %s: %s", filepath, FTErrorString(error));
        return font;
    }

    Log(0, "[Font loader] Rendering font %s at size %d...", filepath, size);

    // Set size for rendering.
    FT_Set_Pixel_Sizes(face, 0, size);

    // Load all printable ASCII characters.
    for (char c = ' '; c < '~'; c++)
        YE_LoadGlyph(font.get(), face, c);

    FT_Done_Face(face);

    return font;
}

