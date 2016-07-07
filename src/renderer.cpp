#include "renderer.h"
#include "geometry.h"
#include "font.h"
#include "math.h"

float tile_width, tile_height, half_width, half_height;
int index;

Light lol;

RectF YE_VisibleWorld()
{
    return RectF(cam->pos.x - half_width,
                 cam->pos.x + half_width,
                 cam->pos.y - half_height,
                 cam->pos.y + half_height);
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
    tile_width = cam->res.x/tile_size;
    tile_height = cam->res.y/tile_size;
    half_width = tile_width/2;
    half_height = tile_height/2;

    //move camera
    cam->pos = player->pos;

    glLoadIdentity();
    glOrtho(0, tile_width, 0, tile_height, -1, 1);
    glTranslatef(-cam->pos.x+half_width, -cam->pos.y+half_height, 0.0f);

    glColor3f(stmap.Rcolor, stmap.Gcolor, stmap.Bcolor);

    //render tiles
    for (Vector2i pos : YE_VisibleTiles())
    {
        int index = stmap.Index2d(pos);
        if(stmap.CheckTile(pos))
            stmap.Tiles[index].Draw(pos);
    }

    glEnable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
    glBlendFunc(GL_DST_COLOR, GL_ZERO);

    //draw fake AO
    for (Vector2i pos : YE_VisibleTiles())
    {
        if(stmap.TileIsSolid(pos))
            YE_DrawAO(pos);
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
    player->DLight->pos = player->pos;
    player->DLight->Draw();

    //test cursor light

    lol.pos = ScreenToWorld(pmouse->pos);
    lol.Draw();

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
    glVertex2f(cam->pos.x-half_width, cam->pos.y-half_height);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(cam->pos.x-half_width, cam->pos.y+half_height);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(cam->pos.x+half_width, cam->pos.y+half_height);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(cam->pos.x+half_width, cam->pos.y-half_height);
    glEnd();

    //draw text
    glLoadIdentity();
    glOrtho(0, cam->res.x, 0, cam->res.y, -1, 1);

    glBlendFunc(GL_ONE, GL_ONE);
    menufont->DrawText(Vector2i(0, 0), ("Deltatime: " + NumberToString(deltatime) + " s").c_str());
    menufont->DrawText(Vector2i(0, 20), ("Tile size: " + NumberToString(tile_size)).c_str());
    menufont->DrawText(Vector2i(0, 40), ("Y: " + NumberToString(player->pos.y)).c_str());
    menufont->DrawText(Vector2i(0, 60), ("X: " + NumberToString(player->pos.x)).c_str());

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    pmouse->NormalCursor->Draw(pmouse->pos);

    glDisable(GL_BLEND);
}
