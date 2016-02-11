#include "common.h"

Tile::Tile()
{}

void Tile::Draw(float x, float y)
{
    GLuint rtexture = Textures[Texture];
    glBindTexture(GL_TEXTURE_2D, rtexture);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(x, y);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(x, y+1.0);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(x+1.0, y+1.0);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(x+1.0, y);
    glEnd();
}
