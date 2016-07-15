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