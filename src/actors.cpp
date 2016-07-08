#include "actors.h"
#include "math.h"
#include "tiles.h"
#include "map.h"
#include "states.h"

#define shadow_scalefactor 1.5f
#define shadowminsize 1.1f

Actor::Actor(Vector2f spawn)
{
    _hp = 100;
    _Shadow = 0;
    _Solid = 0;
    _Noclip = 0;
    _Alpha = 1.0;
    _Speed = 0;
    _Angle = 0;
    _pos = spawn;

    CurrentState = new State;
}

float Actor::x1() const
{
    return _pos.x-whalf();
}

float Actor::x2() const
{
    return _pos.x+whalf();
}

float Actor::y1() const
{
    return _pos.y-hhalf();
}

float Actor::y2() const
{
    return _pos.y+hhalf();
}

float Actor::whalf() const
{
    return _Width/2;
}

float Actor::hhalf() const
{
    return _Height/2;
}

bool Actor::CheckTop() const
{
    int bx1 = floorf(x1());
    int bx2 = floorf(x2()) + 1;
    int by = floorf(y2());

    for(int i = bx1; i < bx2; i++)
    {
        if(stmap.TileIsSolid(Vector2i(i, by)))
            return true;
    }
    return false;
}

bool Actor::CheckBottom() const
{
    int bx1 = floorf(x1());
    int bx2 = floorf(x2()) + 1;
    int by = floorf(y1());

    for(int i = bx1; i < bx2; i++)
    {
        if(stmap.TileIsSolid(Vector2i(i, by)))
            return true;
    }
    return false;
}

bool Actor::CheckLeft() const
{
    int by1 = floorf(y1());
    int by2 = floorf(y2()) + 1;
    int bx = floorf(x1());

    for(int i = by1; i < by2; i++)
    {
        if(stmap.TileIsSolid(Vector2i(bx, i)))
            return true;
    }
    return false;
}

bool Actor::CheckRight() const
{
    int by1 = floorf(y1());
    int by2 = floorf(y2()) + 1;
    int bx = floorf(x2());

    for(int i = by1; i < by2; i++)
    {
        if(stmap.TileIsSolid(Vector2i(bx, i)))
            return true;
    }
    return false;
}

void Actor::CollisionTop()
{
    if(CheckTop() && !_Noclip)
        _pos.y = floorf(_pos.y) + _Height - COLLISION_OFFSET;
}

void Actor::CollisionBottom()
{
    if(CheckBottom() && !_Noclip)
        _pos.y = ceilf(_pos.y) - _Height + COLLISION_OFFSET;
}

void Actor::CollisionLeft()
{
    if(CheckLeft() && !_Noclip)
        _pos.x = ceilf(_pos.x) - _Width + COLLISION_OFFSET;
}

void Actor::CollisionRight()
{
    if(CheckRight() && !_Noclip)
        _pos.x = floorf(_pos.x) + _Width - COLLISION_OFFSET;
}

void Actor::Move(Vector2f vec)
{
    _pos.x += vec.x;

    if(vec.x > 0)
        CollisionRight();
    else if(vec.x < 0)
        CollisionLeft();

    _pos.y += vec.y;

    if(vec.y > 0)
        CollisionTop();
    else if(vec.y < 0)
        CollisionBottom();
}

void Actor::Teleport(Vector2f vec)
{
    _pos = vec;
}

void Actor::Draw()
{
    if(_Shadow && YE_Shadows)
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

    DrawSprite(1.0f, 1.0f, _Alpha);
}

void Actor::DrawSprite(float scale, float saturation, float alpha) const
{
    glBindTexture(GL_TEXTURE_2D, _Sprite);

    float SHalfWidth = _Width/2*scale;
    float SHalfHeight = _Height/2*scale;
    float x = _pos.x;
    float y = _pos.y;

    glBegin(GL_QUADS);
    glColor4f(saturation, saturation, saturation, alpha);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(x-SHalfWidth, y-SHalfHeight);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(x-SHalfWidth, y+SHalfHeight);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(x+SHalfWidth, y+SHalfHeight);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(x+SHalfWidth, y-SHalfHeight);
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
    float x = pos.x;
    float y = pos.y;

    glColor3f(RColor, GColor, BColor);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(x-Radius, y-Radius);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(x-Radius, y+Radius);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(x+Radius, y+Radius);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(x+Radius, y-Radius);
    glEnd();
}

void CreatePlayer(float spawnx, float spawny)
{
    player->SetSolid(true);
    player->SetShadow(true);
    player->Sethp(100);
    player->Teleport(Vector2f(spawnx, spawny));
    player->SetWidth(0.7);
    player->SetHeight(0.7);
    player->SetSpeed(5);
    player->DLight->RColor = 1.0;
    player->DLight->GColor = 0.2;
    player->DLight->BColor = 0.6;
    player->SetSprite(Textures["p_idle_01.png"]);
    player->SetState<PlayerIdleState>();
}
