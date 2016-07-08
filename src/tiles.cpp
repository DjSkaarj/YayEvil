#include "tiles.h"
#include "map.h"

Tile::Tile()
{
    Texture = 0;
    Solid = 0;
}

void Tile::Draw(Vector2i pos)
{
    glBindTexture(GL_TEXTURE_2D, Texture);
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
    return (stmap.TileExists(pos) && !stmap.TileIsSolid(pos));
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
        glColor3f(AO_COLOR, AO_COLOR, AO_COLOR);
        glVertex2f(x, y);
        glVertex2f(x+1, y);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(x+1, y-AO_SIZE);
        glVertex2f(x, y-AO_SIZE);
    }
    if(l_m)
    {
        glColor3f(AO_COLOR, AO_COLOR, AO_COLOR);
        glVertex2f(x, y);
        glVertex2f(x, y+1);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(x-AO_SIZE, y+1);
        glVertex2f(x-AO_SIZE, y);
    }
    if(r_m)
    {
        glColor3f(AO_COLOR, AO_COLOR, AO_COLOR);
        glVertex2f(x+1, y);
        glVertex2f(x+1, y+1);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(x+1+AO_SIZE, y+1);
        glVertex2f(x+1+AO_SIZE, y);
    }
    if(m_b)
    {
        glColor3f(AO_COLOR, AO_COLOR, AO_COLOR);
        glVertex2f(x, y+1);
        glVertex2f(x+1, y+1);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(x+1, y+1+AO_SIZE);
        glVertex2f(x, y+1+AO_SIZE);
    }

    //corners
    if((l_m && l_u && m_u) || (l_u && !l_m && !m_u))
    {
        glColor3f(AO_COLOR, AO_COLOR, AO_COLOR);
        glVertex2f(x, y);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(x-AO_SIZE, y);
        glVertex2f(x-AO_SIZE, y-AO_SIZE);
        glVertex2f(x, y-AO_SIZE);
    }
    if((r_m && r_u && m_u) || (r_u && !r_m && !m_u))
    {
        glColor3f(AO_COLOR, AO_COLOR, AO_COLOR);
        glVertex2f(x+1, y);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(x+1, y-AO_SIZE);
        glVertex2f(x+1+AO_SIZE, y-AO_SIZE);
        glVertex2f(x+1+AO_SIZE, y);
    }
    if((l_m && l_b && m_b) || (l_b && !l_m && !m_b))
    {
        glColor3f(AO_COLOR, AO_COLOR, AO_COLOR);
        glVertex2f(x, y+1);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(x-AO_SIZE, y+1);
        glVertex2f(x-AO_SIZE, y+1+AO_SIZE);
        glVertex2f(x, y+1+AO_SIZE);
    }
    if((m_b && r_b && r_m) || (r_b && !m_b && !r_m))
    {
        glColor3f(AO_COLOR, AO_COLOR, AO_COLOR);
        glVertex2f(x+1, y+1);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(x+1+AO_SIZE, y+1);
        glVertex2f(x+1+AO_SIZE, y+1+AO_SIZE);
        glVertex2f(x+1, y+1+AO_SIZE);
    }

    glEnd();
}
