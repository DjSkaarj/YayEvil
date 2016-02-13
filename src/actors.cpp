#include "common.h"
#define YE_Shadow_Scale 1.12f
#define YE_Shadow_Alpha 0.6f

Actor::Actor()
{}

void Actor::Draw()
{
    if(Shadow && YE_Shadows)
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        DrawSprite(YE_Shadow_Scale, 0.0f, YE_Shadow_Alpha);
    }

    DrawSprite(1.0f, 1.0f, 1.0f);
}

void Actor::DrawSprite(float scale, float saturation, float alpha)
{
    GLuint rpsprite = Textures[Sprite];
    glBindTexture(GL_TEXTURE_2D, rpsprite);

    float SHalfWidth = Width/2*scale;
    float SHalfHeight = Height/2*scale;
    glBegin(GL_QUADS);
    glColor4f(saturation, saturation, saturation, alpha);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(X-SHalfWidth, Y-SHalfHeight);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(X-SHalfWidth, Y+SHalfHeight);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(X+SHalfWidth, Y+SHalfHeight);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(X+SHalfWidth, Y-SHalfHeight);
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
    player->Shadow = 1;
    strcpy(player->Sprite, "p_idle_01.png");
}
