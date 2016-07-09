#ifndef ACTORS_H_INCLUDED
#define ACTORS_H_INCLUDED

#include "common.h"
#include "geometry.h"
#include "states.h"

#define FRICTION_FACTOR 0.01
#define SPEED_FACTOR 0.1

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
    enum Flags
    {
        AF_NONE = 0,
        AF_CLIPBOUNCE
    };

    Actor(Vector2f spawn);
    void Update();
    void Draw();
    void DrawSprite(float scale, float saturation, float alpha) const;

    void Teleport(Vector2f vec);
    void Walk(Vector2f vec);

    Light *DLight = new Light;

    State *CurrentState;
    template<typename T> void SetState();

    GETSET(int, flags)

    FGETSET(ClipBounce, AF_CLIPBOUNCE, _flags)

    GETSET(float, Angle)
    GETSET(float, Alpha)
    GETSET(float, Speed)
    GETSET(float, BounceFactor)
    GETSET(float, Friction)
    GETSET(float, Width)
    GETSET(float, Height)

    GETSET(int, hp)
    GETSET(bool, Shadow)
    GETSET(bool, Solid)
    GETSET(bool, Noclip)

    GETTER(Vector2f, pos)
    GETTER(Vector2f, vel)
    GETSET(GLuint, Sprite)

private:
    int _flags;
    float _Angle, _Alpha, _Speed, _BounceFactor, _Friction, _Width, _Height;
    int _hp;
    bool _Shadow, _Solid, _Noclip;
    Vector2f _pos, _prevpos, _vel;
    GLuint _Sprite;

    // physics
    void UpdatePhysics();
    void Move(Vector2f vec);

    //collision
    void CollisionTop();
    void CollisionBottom();
    void CollisionLeft();
    void CollisionRight();
    bool CheckTop() const;
    bool CheckBottom() const;
    bool CheckLeft() const;
    bool CheckRight() const;
    float x1() const;
    float x2() const;
    float y1() const;
    float y2() const;
    float whalf() const;
    float hhalf() const;
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
