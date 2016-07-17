#include "common.h"
#include "states.h"
#include "actors.h"

std::map<std::string, State*> ActorTypes;

void InitActorTypes()
{
	ActorTypes["cacodemon"] = new CacodemonSpawnState();
	ActorTypes["barrel"] = new BarrelSpawnState();
	ActorTypes["soulsphere"] = new SoulSphereSpawnState();
}

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