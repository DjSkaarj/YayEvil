#include "common.h"
#include "states.h"
#include "actors.h"
#include "map.h"

std::map<std::string, State*> ActorTypes;

void InitActorTypes()
{
	ActorTypes["cacodemon"] = new CacodemonSpawnState();
	ActorTypes["barrel"] = new BarrelSpawnState();
	ActorTypes["soulsphere"] = new SoulSphereSpawnState();
}

void PlayerSpawnState::Enter(Actor *actor)
{
	actor->SetSpriteRotation("p_idle");
	actor->SetSolid(true);
	actor->SetDrawShadow(true);
	actor->Sethp(100);
	actor->Teleport(Vector2f(stmap.PlayerX, stmap.PlayerY));
	actor->SetSize(Vector2f(0.7, 0.7));
	actor->SetSpeed(1.0);
	actor->SetFriction(1.0);
	actor->DLight->RColor = 1.0;
	actor->DLight->GColor = 0.2;
	actor->DLight->BColor = 0.6;
	actor->SetState<PlayerIdleState>();
}

void PlayerSpawnState::Update(Actor *actor)
{}

void PlayerSpawnState::Exit(Actor *actor)
{}

void PlayerIdleState::Enter(Actor *actor)
{}

void PlayerIdleState::Update(Actor *actor)
{
	//actor->SetSpriteRotation("p_idle");
	actor->SetSprite("barre");
}

void PlayerIdleState::Exit(Actor *actor)
{}

void CacodemonSpawnState::Enter(Actor *actor)
{}

void CacodemonSpawnState::Update(Actor *actor)
{}

void CacodemonSpawnState::Exit(Actor *actor)
{}

void BarrelSpawnState::Enter(Actor *actor)
{
	actor->SetSprite("barrel");
}

void BarrelSpawnState::Update(Actor *actor)
{}

void BarrelSpawnState::Exit(Actor *actor)
{}

void SoulSphereSpawnState::Enter(Actor *actor)
{}

void SoulSphereSpawnState::Update(Actor *actor)
{}

void SoulSphereSpawnState::Exit(Actor *actor)
{}