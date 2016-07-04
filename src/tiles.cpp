#include "tiles.h"

#include "map.h"

#define AO_size 0.25
#define AO_color 0.2f

Tile::Tile()
{}

void Tile::Draw(Vector2i pos)
{
    GLuint rtexture = Textures[Texture];
    glBindTexture(GL_TEXTURE_2D, rtexture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(pos.x, pos.y);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(pos.x, pos.y+1.0);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(pos.x+1.0, pos.y+1.0);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(pos.x+1.0, pos.y);
    glEnd();
}

bool YE_CheckAO(Vector2i pos)
{
    return (stmap.CheckTile(pos) && !stmap.TileIsSolid(pos));
}

void YE_DrawAO(Vector2i pos)
{
    int x = pos.x;
    int y = pos.y;

    bool l_u = YE_CheckAO(pos.offset(-1, -1));
    bool m_u = YE_CheckAO(pos.offset(0, -1));
    bool r_u = YE_CheckAO(pos.offset(1, -1));

    bool l_m = YE_CheckAO(pos.offset(-1, 0));
    bool r_m = YE_CheckAO(pos.offset(1, 0));

    bool l_b = YE_CheckAO(pos.offset(-1, 1));
    bool m_b = YE_CheckAO(pos.offset(0, 1));
    bool r_b = YE_CheckAO(pos.offset(1, 1));

    glBegin(GL_QUADS);

    //edges
    if(m_u)
    {
        glColor3f(AO_color, AO_color, AO_color);
        glVertex2f(x, y);
        glVertex2f(x+1, y);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(x+1, y-AO_size);
        glVertex2f(x, y-AO_size);
    }
    if(l_m)
    {
        glColor3f(AO_color, AO_color, AO_color);
        glVertex2f(x, y);
        glVertex2f(x, y+1);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(x-AO_size, y+1);
        glVertex2f(x-AO_size, y);
    }
    if(r_m)
    {
        glColor3f(AO_color, AO_color, AO_color);
        glVertex2f(x+1, y);
        glVertex2f(x+1, y+1);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(x+1+AO_size, y+1);
        glVertex2f(x+1+AO_size, y);
    }
    if(m_b)
    {
        glColor3f(AO_color, AO_color, AO_color);
        glVertex2f(x, y+1);
        glVertex2f(x+1, y+1);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(x+1, y+1+AO_size);
        glVertex2f(x, y+1+AO_size);
    }

    //corners
    if((l_m && l_u && m_u) || (l_u && !l_m && !m_u))
    {
        glColor3f(AO_color, AO_color, AO_color);
        glVertex2f(x, y);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(x-AO_size, y);
        glVertex2f(x-AO_size, y-AO_size);
        glVertex2f(x, y-AO_size);
    }
    if((r_m && r_u && m_u) || (r_u && !r_m && !m_u))
    {
        glColor3f(AO_color, AO_color, AO_color);
        glVertex2f(x+1, y);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(x+1, y-AO_size);
        glVertex2f(x+1+AO_size, y-AO_size);
        glVertex2f(x+1+AO_size, y);
    }
    if((l_m && l_b && m_b) || (l_b && !l_m && !m_b))
    {
        glColor3f(AO_color, AO_color, AO_color);
        glVertex2f(x, y+1);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(x-AO_size, y+1);
        glVertex2f(x-AO_size, y+1+AO_size);
        glVertex2f(x, y+1+AO_size);
    }
    if((m_b && r_b && r_m) || (r_b && !m_b && !r_m))
    {
        glColor3f(AO_color, AO_color, AO_color);
        glVertex2f(x+1, y+1);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(x+1+AO_size, y+1);
        glVertex2f(x+1+AO_size, y+1+AO_size);
        glVertex2f(x+1, y+1+AO_size);
    }

    glEnd();
}
