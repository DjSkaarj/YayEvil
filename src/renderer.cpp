#include "renderer.h"
#include "geometry.h"
#include "font.h"
#include "math.h"

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
    return YE_VisibleWorld().toInt().intersect(stmap.Rect());
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
    for (Vector2i pos : YE_VisibleTiles())
    {
        int index = YE_Index2D(pos.x, pos.y, stmap.Width);
        if(YE_CheckTile(pos.x, pos.y))
            stmap.Tiles[index].Draw(pos.x, pos.y);
    }

    //draw fake AO
    glEnable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glBlendFunc(GL_DST_COLOR, GL_ZERO);

    //draw fake AO
    for (Vector2i pos : YE_VisibleTiles())
    {
        if(YE_CheckIfSolid(pos.x, pos.y))
            YE_DrawAO(pos.x, pos.y);
    }

    //render player
    glEnable(GL_TEXTURE_2D);
    glColor3f(stmap.Rcolor, stmap.Gcolor, stmap.Bcolor);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    player->Draw();

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

    //draw text
    glLoadIdentity();
    glOrtho(0, screen_width, 0, screen_height, -1, 1);

    glBlendFunc(GL_ONE, GL_ONE);
    menufont->DrawText(Vector2i(0, 0), ("Deltatime: " + NumberToString(deltatime) + " s").c_str());
    menufont->DrawText(Vector2i(0, 20), ("Y: " + NumberToString(player->Y)).c_str());
    menufont->DrawText(Vector2i(0, 40), ("X: " + NumberToString(player->X)).c_str());

    glColor3f(1.0f, 0.5f, 0.0f);
    Vector2f vec = ScreenToWorld(pmouse->pos);
    std::string test = NumberToString(vec.x) + " " + NumberToString(vec.y);
    menufont->DrawText(Vector2i(std::min(pmouse->pos.x, screen_width - 120), std::min(pmouse->pos.y, screen_height-15)), test.c_str());
    glColor3f(1.0f, 1.0f, 1.0f);

    glDisable(GL_BLEND);
}
