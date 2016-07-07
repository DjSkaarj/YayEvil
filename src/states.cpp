#include "states.h"
#include "actors.h"

template<typename T> void Actor::SetState()
{
    CurrentState->Exit(this);

    delete CurrentState;
    CurrentState = new T();
    CurrentState->Enter(this);
}
