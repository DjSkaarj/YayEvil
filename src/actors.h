#ifndef ACTORS_H_INCLUDED
#define ACTORS_H_INCLUDED

#include "common.h"
#include "geometry.h"

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

    float X, Y, Radius, RColor, GColor, BColor;

    RectF Rect() { return RectF(X - Radius, X + Radius, Y - Radius, Y + Radius); }
};

class Actor
{
public:
    Actor();
    void Draw();
    void DrawSprite(float scale, float saturation, float alpha);

    int HP;
    bool Shadow, Solid, Noclip;
    float X, Y, Alpha, Speed, Width, Height;
    Light* DLight = new Light;
    char Sprite[255];

    float whalf();
    float hhalf();

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();

    void CollisionTop();
    void CollisionBottom();
    void CollisionLeft();
    void CollisionRight();

private:
    bool CheckTop();
    bool CheckBottom();
    bool CheckLeft();
    bool CheckRight();
    float x1();
    float x2();
    float y1();
    float y2();
};

void CreatePlayer(float spawnx, float spawny);
extern Actor *player;

#endif // ACTORS_H_INCLUDED
