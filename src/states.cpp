#include "common.h"
#include "states.h"
#include "actors.h"
#include "map.h"
#include "log.h"
#include "animation.h"

std::map<std::string, State*> ActorTypes;

void InitActorTypes()
{
	ActorTypes["cacodemon"] = new CacodemonSpawnState();
	ActorTypes["barrel"] = new BarrelSpawnState();
	ActorTypes["soulsphere"] = new SoulSphereSpawnState();
}

void PlayerSpawnState::Enter(Actor *actor)
{
	actor->SetName("Player");
	actor->SetSpriteRotation("p_idle");
	actor->SetSolid(true);
	actor->SetDrawShadow(true);
	actor->Sethp(100);
	actor->Teleport(Vector2f(stmap.PlayerX, stmap.PlayerY));
	actor->SetSize(Vector2f(0.7, 0.7));
	actor->SetSpeed(1.0);
	actor->SetFriction(1.0);
	actor->DLight->SetColor(1.0, 0.2, 0.6);
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
	actor->SetSpriteRotation("p_idle");
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
	actor->Setz(1);
	actor->Anim = AnimBarrel;
	actor->SetSize(Vector2f(0.4, 0.6));
	actor->SetSolid(true);
	actor->SetDrawShadow(true);
	actor->DLight->Radius = 1.0;
	actor->DLight->SetColor(0.2, 0.5, 0.2);
}

void BarrelSpawnState::Update(Actor *actor)
{
	actor->Anim.Update();
	actor->SetSprite(actor->Anim.GetSprite());
}

void BarrelSpawnState::Exit(Actor *actor)
{}

void SoulSphereSpawnState::Enter(Actor *actor)
{}

void SoulSphereSpawnState::Update(Actor *actor)
{}

void SoulSphereSpawnState::Exit(Actor *actor)
{}