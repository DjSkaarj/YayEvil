#include "common.h"
#include "actors.h"
#include "math.h"
#include "tiles.h"
#include "map.h"
#include "states.h"
#include "mouse.h"

Actor::Actor(Vector2f spawn)
{
    _hp = 100;
    _Alpha = 1.0;
    _Speed = 0;
    _Angle = 0;
    _pos = spawn;
    _vel = Vector2f(0, 0);
    _Friction = 1.0;
    _BounceFactor = 0;
	_Name = "New Actor";

    CurrentState = new State;
}

void Actor::Update()
{
    UpdatePhysics();
    CurrentState->Update(this);
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
    return _Size.x/2;
}

float Actor::hhalf() const
{
    return _Size.y/2;
}

void Actor::UpdatePhysics()
{
    if (_vel.x != 0 || _vel.y != 0)
        Move(_vel);

    //process friction
    Vector2f newvel(fabs(_vel.x), fabs(_vel.y));

    if (newvel.x > 0)
        newvel.x -= _Friction * FRICTION_FACTOR;
    if (newvel.x < 0)
        newvel.x = 0;

    if (newvel.y > 0)
        newvel.y -= _Friction * FRICTION_FACTOR;
    if (newvel.y < 0)
        newvel.y = 0;

    _vel = Vector2f(newvel.x * sign(_vel.x), newvel.y * sign(_vel.y));
}

bool Actor::CheckActorCollision() const
{
	for (Actor &actor : stmap.Actors)
	{
		if (this->BoundingBox().intersects(actor.BoundingBox()))
			return true;
	}
	return false;
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
		CheckActorCollision();
    }
	return false; // useless shit for successful compilation
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
		CheckActorCollision();
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
		CheckActorCollision();
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
		CheckActorCollision();
    }
	return false;
}

void Actor::CollisionTop()
{
    if(CheckTop() && !(_flags & AF_NOCLIP))
    {
        _pos.y = floorf(_pos.y) + _Size.y - COLLISION_OFFSET;

        if (((_flags & AF_CLIPBOUNCE) && (_prevpos.y != _pos.y)) || !(_flags & AF_CLIPBOUNCE))
            _vel.y *= - _BounceFactor;
    }
}

void Actor::CollisionBottom()
{
    if(CheckBottom() && !(_flags & AF_NOCLIP))
    {
        _pos.y = ceilf(_pos.y) - _Size.y + COLLISION_OFFSET;

        if (((_flags & AF_CLIPBOUNCE) && (_prevpos.y != _pos.y)) || !(_flags & AF_CLIPBOUNCE))
            _vel.y *= - _BounceFactor;
    }
}

void Actor::CollisionLeft()
{
    if(CheckLeft() && !(_flags & AF_NOCLIP))
    {
        _pos.x = ceilf(_pos.x) - _Size.x + COLLISION_OFFSET;

        if (((_flags & AF_CLIPBOUNCE) && (_prevpos.x != _pos.x)) || !(_flags & AF_CLIPBOUNCE))
            _vel.x *= - _BounceFactor;
    }
}

void Actor::CollisionRight()
{
    if(CheckRight() && !(_flags & AF_NOCLIP))
    {
        _pos.x = floorf(_pos.x) + _Size.x - COLLISION_OFFSET;

        if (((_flags & AF_CLIPBOUNCE) && (_prevpos.x != _pos.x)) || !(_flags & AF_CLIPBOUNCE))
            _vel.x *= - _BounceFactor;
    }
}

void Actor::Move(Vector2f vec)
{
    _Angle = vec.angle();
    _prevpos.x = _pos.x;
    _pos.x += vec.x;

    if(vec.x > 0)
        CollisionRight();
    else if(vec.x < 0)
        CollisionLeft();

    _prevpos.y = _pos.y;
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

void Actor::SetVelocity(Vector2f vec)
{
    _vel = vec;
}

void Actor::Draw()
{
    if((_flags2 & AF2_DRAWSHADOW) && YE_Shadows)
    {
        float YE_ShadowScale = YE_ShadowScaleA * SHADOW_SCALEFACTOR;
        float alpha = YE_ShadowIntensity / YE_ShadowQuality;

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        for (int i = 0; i < YE_ShadowQuality; i++)
        {
            float ssize = lerp(SHADOW_MINSIZE, YE_ShadowScale, float((i + 0.5) / YE_ShadowQuality));
            DrawSprite(ssize, 0.0f, alpha);
        }
    }

    DrawSprite(1.0f, 1.0f, _Alpha);
}
 
void Actor::DrawSprite(float scale, float saturation, float alpha) const
{
    glBindTexture(GL_TEXTURE_2D, _Sprite);

	float width = whalf();
	float height = hhalf();

	float x = _pos.x;
    float y = _pos.y;

    glBegin(GL_QUADS);
    glColor4f(saturation, saturation, saturation, alpha);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(x - width, y - height);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(x - width, y + height);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(x + width, y + height);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(x + width, y - height);
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
    glVertex2f(x - Radius, y - Radius);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(x - Radius, y + Radius);
    glTexCoord2f(0.0, 0.0);
    glVertex2f(x + Radius, y + Radius);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(x + Radius, y - Radius);
    glEnd();
}

void CreatePlayer(float spawnx, float spawny)
{
    player->actor = playerpawn;

    playerpawn->SetSolid(true);
    playerpawn->SetDrawShadow(true);
    playerpawn->Sethp(100);
    playerpawn->Teleport(Vector2f(spawnx, spawny));
	playerpawn->SetSize(Vector2f(0.7, 0.7));
    playerpawn->SetSpeed(1.0);
    playerpawn->SetFriction(1.0);
    playerpawn->DLight->RColor = 1.0;
    playerpawn->DLight->GColor = 0.2;
    playerpawn->DLight->BColor = 0.6;
    playerpawn->SetSprite(Textures["p_idle_01.png"]);
    playerpawn->SetState<PlayerIdleState>();
	//playerpawn->SetBounceFactor(0.5);
	//playerpawn->SetClipBounce(true);
}

void Player::InventoryRadius() const
{
	for (Actor &actor : stmap.Actors)
	{
		if(actor.IfInventory() && InvRect().contains(actor.pos()))
		{
			glLoadIdentity();
			glOrtho(0, cam->res.x, 0, cam->res.y, -1, 1);
			glBlendFunc(GL_ONE, GL_ONE);
			
			menufont->DrawText(WorldToScreen(actor.pos()), actor.Name().c_str());
		}
	}
}