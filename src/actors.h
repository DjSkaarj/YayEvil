#ifndef ACTORS_H_INCLUDED
#define ACTORS_H_INCLUDED

#include "common.h"
#include "geometry.h"
#include "font.h"
#include "animation.h"

#define FRICTION_FACTOR 0.1F
#define COLLISION_OFFSET 0.06F
#define SHADOW_SCALEFACTOR 1.5f
#define SHADOW_MINSIZE 1.1f
#define INVENTORY_RADIUS 5

class YE_Map;
class Camera;
class State;

extern bool YE_Shadows;
extern int YE_ShadowQuality;
extern float YE_ShadowIntensity;
extern float YE_ShadowScaleA;
extern YE_Map stmap;

extern Font *font;
extern Font *menufont;

extern Camera *cam;

extern float deltatime;

class Light
{
public:
    Light();
    void Draw() const;
	void SetColor(float R, float G, float B);

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
        AF_CLIPBOUNCE = 1,
        AF_NOCLIP = 2,
        AF_SOLID = 4,
        AF_INVENTORY = 8
    };
    enum Flags2
    {
        AF2_NONE = 0,
        AF2_DRAWSHADOW = 1
    };

    Actor(Vector2f spawn);

    void Update();
    void Draw();
    void DrawSprite(float scale, float saturation, float alpha) const;

	void SetSprite(std::string name);
	void SetSpriteRotation(std::string name);

    void Teleport(Vector2f vec);
    void SetVelocity(Vector2f vec);

    Light *DLight = new Light;
	Animation Anim;

    State *CurrentState;
    template<typename T> void SetState();

	GETSET(int, flags)
	GETSET(int, flags2)

	FGETSET(ClipBounce, AF_CLIPBOUNCE, flags)
	FGETSET(NoClip, AF_NOCLIP, flags)
	FGETSET(Solid, AF_SOLID, flags)
	FGETSET(IfInventory, AF_INVENTORY, flags)

	FGETSET(DrawShadow, AF2_DRAWSHADOW, flags2)

	GETSET(float, Angle)
	GETSET(float, Alpha)
	GETSET(float, Speed)
	GETSET(float, BounceFactor)
	GETSET(float, Friction)
	GETSET(Vector2f, Size)

	GETSET(int, hp)

	GETTER(Vector2f, pos)
	GETTER(Vector2f, prevpos)
	GETTER(Vector2f, vel)
	GETTER(GLuint, Sprite)

	GETSET(std::string, Name)

	RectF BoundingBox() const {
		return RectF(_pos.x - _Size.x,
			_pos.x + _Size.x,
			_pos.y - _Size.y,
			_pos.y - _Size.y);
	}

private:
    int _flags, _flags2;
	float _Angle, _Alpha, _Speed, _BounceFactor, _Friction;
    int _hp;
    Vector2f _Size, _pos, _prevpos, _vel;
    GLuint _Sprite;
	std::string _Name;

    // physics
    void UpdatePhysics();
    void Move(Vector2f vec);

    //collision
    void CollisionTop();
    void CollisionBottom();
    void CollisionLeft();
    void CollisionRight();
	bool CheckActorCollision() const;
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

int SpriteNumForAngle(float a);

class Player
{
public:
    Player() {};
    Actor* GetActor() const { return actor; }

	RectF InvRect() const {
		return RectF(GetActor()->pos().x - INVENTORY_RADIUS,
			GetActor()->pos().x + INVENTORY_RADIUS,
			GetActor()->pos().y - INVENTORY_RADIUS,
			GetActor()->pos().y + INVENTORY_RADIUS);
	}
	void InventoryRadius() const;

    Actor *actor;
    std::vector<Actor> Inventory;
};

void CreatePlayer();
extern Actor *playerpawn;
extern Player *player;

#endif // ACTORS_H_INCLUDED
