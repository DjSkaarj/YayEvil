#include "common.h"

Actor::Actor()
{}

void Actor::Draw()
{
    GLuint rpsprite = Textures[Sprite];
    glBindTexture(GL_TEXTURE_2D, rpsprite);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(X-Width/2, Y-Height/2);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(X-Width/2, Y+Height/2);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(X+Width/2, Y+Height/2);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(X+Width/2, Y-Height/2);
    glEnd();
}

Light::Light()
{
    Radius = 2.0;
    RColor = 1.0;
    GColor = 1.0;
    BColor = 1.0;
}

void Light::Draw()
{
    glColor3f(RColor, GColor, BColor);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(X-Radius, Y-Radius);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(X-Radius, Y+Radius);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(X+Radius, Y+Radius);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(X+Radius, Y-Radius);
    glEnd();
}

void CreatePlayer(float spawnx, float spawny)
{
    player->HP = 100;
    player->X = spawnx;
    player->Y = spawny;
    player->Width = 0.7;
    player->Height = 0.7;
    player->Speed = 5;
    player->DLight->RColor = 1.0;
    player->DLight->GColor = 0.2;
    player->DLight->BColor = 0.6;
    strcpy(player->Sprite, "p_idle_01.png");
}
