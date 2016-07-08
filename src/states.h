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
};

#endif // STATES_H_INCLUDED
