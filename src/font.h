#ifndef TEXTRENDER_H_INCLUDED
#define TEXTRENDER_H_INCLUDED

#include "common.h"
#include "geometry.h"

class Glyph
{
public:
    Glyph(GLuint texture, Vector2i size, Vector2f offset, Vector2f advance);
    ~Glyph();

    GLuint Texture() const;
    Vector2i Size() const;
    Vector2f Offset() const;
    Vector2f Advance() const;

private:
    GLuint mTexture;
    Vector2i mSize;
    Vector2f mOffset;
    Vector2f mAdvance;
};

class Font
{
public:
    Font(unique_ptr<Glyph> defaultGlyph);
    void SetGlyph(char c, unique_ptr<Glyph> glyph);

    const Glyph* GetGlyph(char c) const;
    void DrawText(Vector2f pos, const char *text);

private:
    // Map of characters to glyphs.
    std::unordered_map<char, unique_ptr<Glyph>> mGlyphs;

    // A default glyph to return if a character is not present in the font.
    unique_ptr<Glyph> mDefaultGlyph;
};

#endif // TEXTRENDER_H_INCLUDED
