#include "common.h"

#include "geometry.h"

float tiles_width, tiles_height, half_width, half_height;
int index;

RectF YE_VisibleWorld()
{
    return RectF(cam_x - half_width,
                 cam_x + half_width,
                 cam_y - half_height,
                 cam_y + half_height);
}

RectI YE_VisibleTiles()
{
    RectF w = YE_VisibleWorld();
    return RectI(floor(w.xMin), ceil(w.xMax), floor(w.yMin), ceil(w.yMax)).intersect(stmap.Rect());
}

void YE_Renderer()
{
    glClearColor(stmap.BGRcolor, stmap.BGGcolor, stmap.BGBcolor, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //calculate screen size in tiles
    tiles_width = screen_width/64.0;
    tiles_height = screen_height/64.0;
    half_width = tiles_width/2;
    half_height = tiles_height/2;

    //move camera
    cam_x = player->X;
    cam_y = player->Y;
    glLoadIdentity();
    glOrtho(0, tiles_width, 0, tiles_height, -1, 1);
    glTranslatef(-cam_x+half_width, -cam_y+half_height, 0.0f);

    glColor3f(stmap.Rcolor, stmap.Gcolor, stmap.Bcolor);

    //render tiles
    RectI vistiles = YE_VisibleTiles();
    for (Vector2i pos : YE_VisibleTiles())
    {
        int index = YE_Index2D(pos.x, pos.y, stmap.Width);
        if(YE_CheckTile(pos.x, pos.y))
            stmap.Tiles[index].Draw(pos.x, pos.y);
    }

    glEnable(GL_BLEND);

    glColor3f(stmap.Rcolor, stmap.Gcolor, stmap.Bcolor);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //render player
    player->Draw();

    glBlendFunc(GL_DST_COLOR, GL_ZERO);

    //draw fake AO
    for (Vector2i pos : YE_VisibleTiles())
    {
        if(YE_CheckIfSolid(pos.x, pos.y))
            YE_DrawAO(pos.x, pos.y);
    }

    //render lights
    //turn on FBO
    glBindFramebuffer(GL_FRAMEBUFFER, Lightbuffer);
    glClearColor(stmap.ARcolor, stmap.AGcolor, stmap.ABcolor, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);


    glBlendFunc(GL_ONE, GL_ONE);
    glBindTexture(GL_TEXTURE_2D, Textures["light.png"]);

    //render player's light
    player->DLight->X = player->X; // <-|--- !REMOVE THIS CRAP!
    player->DLight->Y = player->Y; // <-|
    player->DLight->Draw();

    //draw map lights
    for (Light &light : stmap.Lights)
    {
        if (light.Rect().intersects(YE_VisibleWorld()))
            light.Draw();
    }

    glColor3f(1.0f, 1.0f, 1.0f);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBlendFunc(GL_DST_COLOR, GL_ZERO);
    glBindTexture(GL_TEXTURE_2D, Lightbuffer);

    //render lightmap
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(cam_x-half_width, cam_y-half_height);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(cam_x-half_width, cam_y+half_height);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(cam_x+half_width, cam_y+half_height);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(cam_x+half_width, cam_y-half_height);
    glEnd();

    glDisable(GL_BLEND);
}
