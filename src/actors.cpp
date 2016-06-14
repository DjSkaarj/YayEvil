#include "actors.h"
#include "math.h"
#include "tiles.h"
#include "map.h"

#define shadow_scalefactor 1.5f
#define shadowminsize 1.1f

Actor::Actor()
{
    HP = 100;
    Shadow = 0;
    Solid = 0;
    Noclip = 0;
    Alpha = 1.0;
    Speed = 0;
}

float Actor::x1()
{
    return X-whalf();
}

float Actor::x2()
{
    return X+whalf();
}

float Actor::y1()
{
    return Y-hhalf();
}

float Actor::y2()
{
    return Y+hhalf();
}

float Actor::whalf()
{
    return Width/2;
}

float Actor::hhalf()
{
    return Height/2;
}

bool Actor::CheckTop()
{
    int bx1 = floorf(x1());
    int bx2 = floorf(x2()) + 1;
    int by = floorf(y2());

    for(int i = bx1; i < bx2; i++)
    {
        if(YE_CheckIfSolid(i, by))
            return true;
    }
    return false;
}

bool Actor::CheckBottom()
{
    int bx1 = floorf(x1());
    int bx2 = floorf(x2()) + 1;
    int by = floorf(y1());

    for(int i = bx1; i < bx2; i++)
    {
        if(YE_CheckIfSolid(i, by))
            return true;
    }
    return false;
}

bool Actor::CheckLeft()
{
    int by1 = floorf(y1());
    int by2 = floorf(y2()) + 1;
    int bx = floorf(x1());

    for(int i = by1; i < by2; i++)
    {
        if(YE_CheckIfSolid(bx, i))
            return true;
    }
    return false;
}

bool Actor::CheckRight()
{
    int by1 = floorf(y1());
    int by2 = floorf(y2()) + 1;
    int bx = floorf(x2());

    for(int i = by1; i < by2; i++)
    {
        if(YE_CheckIfSolid(bx, i))
            return true;
    }
    return false;
}

void Actor::CollisionTop()
{
    if(CheckTop() && !Noclip)
        Y = floorf(Y) + Height - 0.1;
}

void Actor::CollisionBottom()
{
    if(CheckBottom() && !Noclip)
        Y = ceilf(Y) - Height + 0.1;
}

void Actor::CollisionLeft()
{
    if(CheckLeft() && !Noclip)
        X = ceilf(X) - Width + 0.1;
}

void Actor::CollisionRight()
{
    if(CheckRight() && !Noclip)
        X = floorf(X) + Width - 0.1;
}

void Actor::Move(Vector2f vec)
{
    if(vec == Vector2f(0, 0))
    {
        vec.x /= SQRT_2;
        vec.y /= SQRT_2;
    }

    X += vec.x;

    if(vec.x > 0)
        CollisionRight();
    else if(vec.x < 0)
        CollisionLeft();

    Y += vec.y;

    if(vec.y > 0)
        CollisionTop();
    else if(vec.y < 0)
        CollisionBottom();
}

void Actor::Draw()
{
    if(Shadow && YE_Shadows)
    {
        float YE_ShadowScale = YE_ShadowScaleA*shadow_scalefactor;
        float alpha = YE_ShadowIntensity / YE_ShadowQuality;

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        for (int i = 0; i < YE_ShadowQuality; i++)
        {
            float ssize = lerp(shadowminsize, YE_ShadowScale, float((i + 0.5) / YE_ShadowQuality));
            DrawSprite(ssize, 0.0f, alpha);
        }
    }

    DrawSprite(1.0f, 1.0f, Alpha);
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
    player->Solid = true;
    player->Shadow = true;
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
