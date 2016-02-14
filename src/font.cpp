#include "font.h"

// Create a new glyph from a texture.
Glyph::Glyph(GLuint texture, Vector2i size, Vector2f offset, Vector2f advance)
{
    mTexture = texture;
    mSize = size;
    mOffset = offset;
    mAdvance = advance;
}

// Delete the glyph from memory.
Glyph::~Glyph()
{
    glDeleteTextures(1, &mTexture);
}

// The texture with the glyph.
GLuint Glyph::Texture() const
{
    return mTexture;
}

// The size of the glyph.
Vector2f Glyph::Offset() const
{
    return mOffset;
}

// The offset of the glyph relative to the drawing cursor.
Vector2i Glyph::Size() const
{
    return mSize;
}

// The offset to apply to the drawing cursor after drawing the glyph.
Vector2f Glyph::Advance() const
{
    return mAdvance;
}

// Create an empty font with a default glyph to replace missing glyphs.
Font::Font(unique_ptr<Glyph> defaultGlyph):
    mDefaultGlyph(std::move(defaultGlyph))
{
}

// Replace a glyph in the font.
void Font::SetGlyph(char c, unique_ptr<Glyph> glyph)
{
    mGlyphs[c] = std::move(glyph);
}

// Get a glyph from the font.
const Glyph* Font::GetGlyph(char c) const
{
    auto it = mGlyphs.find(c);
    if (it == mGlyphs.end())
        return mDefaultGlyph.get();
    return it->second.get();
}

// Draw a line of text using the font.
void Font::DrawText(Vector2f pos, const char *text)
{
    Vector2f cursor = pos;

    for (const char *p = text; *p != 0; p++)
    {
        auto glyph = GetGlyph(*p);

        Vector2f d = cursor + glyph->Offset();
        Vector2f s = glyph->Size();

        glBindTexture(GL_TEXTURE_2D, glyph->Texture());
        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 1.0);
        glVertex2f(d.x, d.y);
        glTexCoord2f(0.0, 0.0);
        glVertex2f(d.x, d.y - s.y);
        glTexCoord2f(1.0, 0.0);
        glVertex2f(d.x + s.x, d.y - s.y);
        glTexCoord2f(1.0, 1.0);
        glVertex2f(d.x + s.x, d.y);
        glEnd();

        cursor += glyph->Advance();
    }
}
