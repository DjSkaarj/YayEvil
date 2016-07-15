#ifndef STATES_H_INCLUDED
#define STATES_H_INCLUDED

#include "common.h"

class Actor;

class State
{
public:
    virtual ~State() {}

    virtual void Enter(Actor* actor) {}
    virtual void Update(Actor* actor) {}
    virtual void Exit(Actor* actor) {}
	virtual State* Clone() { return new State(*this); }
};

class PlayerIdleState : public State
{
public:
    void Enter(Actor *actor)
    {}
    void Update(Actor *actor)
    {}
    void Exit(Actor *actor)
    {}
	State* clone() { return new PlayerIdleState(*this); }
};

class CacodemonSpawnState : public State
{
public:
	void Enter(Actor *actor)
	{}
	void Update(Actor *actor)
	{}
	void Exit(Actor *actor)
	{}
	State* Clone() { return new CacodemonSpawnState(*this); }
};

class BarrelSpawnState : public State
{
public:
	void Enter(Actor *actor)
	{}
	void Update(Actor *actor)
	{}
	void Exit(Actor *actor)
	{}
	State* Clone() { return new BarrelSpawnState(*this); }
};

class SoulSphereSpawnState : public State
{
public:
	void Enter(Actor *actor)
	{}
	void Update(Actor *actor)
	{}
	void Exit(Actor *actor)
	{}
	State* Clone() { return new SoulSphereSpawnState(*this); }
};

void InitActorTypes();

#endif // STATES_H_INCLUDED
