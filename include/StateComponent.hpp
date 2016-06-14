#ifndef STATECOMPONENT_HPP
#define STATECOMPONENT_HPP

#include "Component.hpp"

enum State
{
	IDLE,
	WALKING,
	JUMPING,
	FALLING,
	ATTACKING,
	ZIPLINE,
	SHOOT
};

enum UmbrellaState
{
	OPEN, 
	CLOSED
};

enum UmbrellaDirection
{
	UP,
	DOWN,
	FRONT,
	BACK
};

class StateComponent : public Component
{
public:
	StateComponent() : state_(IDLE) {}

	State state_;
	bool facingRight_;
};


class PlayerStateComponent : public StateComponent
{
public:
	PlayerStateComponent() : StateComponent(), umbrellaState_(CLOSED), umbrellaDirection_(DOWN) {}

	UmbrellaState umbrellaState_;
	UmbrellaDirection umbrellaDirection_;
};


#endif