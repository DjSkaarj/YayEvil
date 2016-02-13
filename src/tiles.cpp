#include "common.h"

#define AO_size 0.25
#define AO_color 0.2f

Tile::Tile()
{}

void Tile::Draw(int x, int y)
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

bool YE_CheckTile(int x, int y)
{
    if (!stmap.Rect().contains(x, y))
        return false;

    int index = YE_Index2D(x, y, stmap.Width);
    if (!strcmp(stmap.Tiles[index].Texture, "none"))
        return false;
    return true;
}

bool YE_CheckIfSolid(int x, int y)
{
    int index = YE_Index2D(x, y, stmap.Width);
    return stmap.Tiles[index].Solid;
}

void YE_DrawAO(int x, int y)
{
    /*
    (x-1; y-1)   (x; y-1)    (x+1; y-1)
    (x-1; y)     (x; y)      (x+1; y)
    (x-1; y+1)   (x; y+1)    (x+1; y+1)
    */

    bool l_u = (YE_CheckTile(x-1, y-1) && !YE_CheckIfSolid(x-1, y-1));
    bool m_u = (YE_CheckTile(x, y-1) && !YE_CheckIfSolid(x, y-1));
    bool r_u = (YE_CheckTile(x+1, y-1) && !YE_CheckIfSolid(x+1, y-1));

    bool l_m = (YE_CheckTile(x-1, y) && !YE_CheckIfSolid(x-1, y));
    bool r_m = (YE_CheckTile(x+1, y) && !YE_CheckIfSolid(x+1, y));

    bool l_b = (YE_CheckTile(x-1, y+1) && !YE_CheckIfSolid(x-1, y+1));
    bool m_b = (YE_CheckTile(x, y+1) && !YE_CheckIfSolid(x, y+1));
    bool r_b = (YE_CheckTile(x+1, y+1) && !YE_CheckIfSolid(x+1, y+1));

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
    if((r_m && r_u && m_u) || (r_u && !r_m && m_u))
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
