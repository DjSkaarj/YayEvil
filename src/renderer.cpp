#include "common.h"

float tiles_width, tiles_height, half_width, half_height;
int xmin, ymin, xmax, ymax, index;

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

    //calculate size of visible map part in tiles
    xmin = floor(cam_x-half_width);
    xmax = ceil(cam_x+half_width);
    ymin = floor(cam_y-half_height);
    ymax = ceil(cam_y+half_height);

    //check calculated values
    if(xmin<0) xmin=0;
    if(xmax>stmap.Width-1) xmax = stmap.Width-1;
    if(ymin<0) ymin=0;
    if(ymax>stmap.Height-1) ymax = stmap.Height-1;

    glColor3f(stmap.Rcolor, stmap.Gcolor, stmap.Bcolor);

    //render tiles
    for(int x = xmin; x <= xmax; x++)
    for(int y = ymin; y <= ymax; y++)
    {
        int index = YE_Index2D(x, y, stmap.Width);
        if(YE_CheckTile(x, y))
            stmap.Tiles[index].Draw(x, y);
    }

    glEnable(GL_BLEND);

    glColor3f(stmap.Rcolor, stmap.Gcolor, stmap.Bcolor);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //render player
    player->Draw();

    glBlendFunc(GL_DST_COLOR, GL_ZERO);

    //draw fake AO
    for(int x = xmin; x <= xmax; x++)
    for(int y = ymin; y <= ymax; y++)
    {
        if(YE_CheckIfSolid(x, y))
            YE_DrawAO(x, y);
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
    for(int i = 0; i < stmap.Lights.size(); i++)
    {
        /*float x = stmap.Lights[i].X;
        float y = stmap.Lights[i].Y;
        float rad = stmap.Lights[i].Radius;
        if( (((x+rad)>=xmin) && ((x-rad)<=xmax)) || (((y+rad)>=ymin) && ((y-rad)<=ymax)) )*/
            stmap.Lights[i].Draw();
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
