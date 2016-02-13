#include "common.h"
#define shadow_scalefactor 1.5f
#define shadowminsize 1.1f

Actor::Actor()
{}

void Actor::Draw()
{
    if(Shadow && YE_Shadows)
    {
        float YE_ShadowScale = YE_ShadowScale*shadow_scalefactor;
        float alpha = YE_ShadowIntensity / YE_ShadowQuality;

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        for (int i = 0; i < YE_ShadowQuality; i++)
        {
            float ssize = lerp(shadowminsize, YE_ShadowScale, float((i + 0.5) / YE_ShadowQuality));
            DrawSprite(ssize, 0.0f, alpha);
        }
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
