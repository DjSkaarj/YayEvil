#ifndef ACTORS_H_INCLUDED
#define ACTORS_H_INCLUDED

#include "geometry.h"

extern bool YE_Shadows;
extern int YE_ShadowQuality;
extern float YE_ShadowIntensity;
extern float YE_ShadowScale;

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

    int Solid, HP;
    bool Shadow;
    float X, Y, Alpha, Speed, Width, Height;
    Light* DLight = new Light;
    char Sprite[255];
};

void CreatePlayer(float spawnx, float spawny);
extern Actor *player;

#endif // ACTORS_H_INCLUDED
