#ifndef ACTORS_H_INCLUDED
#define ACTORS_H_INCLUDED

#include "common.h"
#include "geometry.h"
#include "states.h"

class YE_Map;

extern bool YE_Shadows;
extern int YE_ShadowQuality;
extern float YE_ShadowIntensity;
extern float YE_ShadowScaleA;
extern YE_Map stmap;

extern float deltatime;

class Light
{
public:
    Light();
    void Draw();

    Vector2f pos;
    float Radius, RColor, GColor, BColor;

    RectF Rect() { return RectF(pos.x - Radius, pos.x + Radius, pos.y - Radius, pos.y + Radius); }
};

class Actor
{
public:
    Actor();
    void Draw();
    void DrawSprite(float scale, float saturation, float alpha);

    void CollisionTop();
    void CollisionBottom();
    void CollisionLeft();
    void CollisionRight();

    void Move(Vector2f vec);

    Vector2f pos;

    int HP;
    bool Shadow, Solid, Noclip;
    float Alpha, Speed, Width, Height;
    Light *DLight = new Light;
    char Sprite[255];

    float Angle;
    State *CurrentState;
    template<typename T> void SetState();

private:
    bool CheckTop();
    bool CheckBottom();
    bool CheckLeft();
    bool CheckRight();
    float x1();
    float x2();
    float y1();
    float y2();
    float whalf();
    float hhalf();
};

template<typename T> void Actor::SetState()
{
    CurrentState->Exit(this);

    delete CurrentState;
    CurrentState = new T();
    CurrentState->Enter(this);
}

void CreatePlayer(float spawnx, float spawny);
extern Actor *player;

#endif // ACTORS_H_INCLUDED
