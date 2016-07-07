#ifndef STATES_H_INCLUDED
#define STATES_H_INCLUDED

#include "common.h"
#include "actors.h"

class State
{
    virtual ~State() {}

    virtual void Enter(Actor* actor) {}
    virtual void Update(Actor* actor) {}
    virtual void Exit(Actor* actor) {}
};

#endif // STATES_H_INCLUDED
