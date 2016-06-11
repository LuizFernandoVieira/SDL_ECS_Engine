#ifndef STATECOMPONENT_HPP
#define STATECOMPONENT_HPP

#include "Component.hpp"

/*class EntityStateMachine;
class EntityState;

enum StateMachineType
{
	PLAYER,
	ENEMY,
	OBJECT
};

class StateComponent : public Component
{
public:
	StateComponent(StateMachineType type = PLAYER);
	~StateComponent() {}

	EntityStateMachine* getStateMachine() { return stateMachine_; }
	void setStateMachine(EntityStateMachine& stateMachine, StateMachineType type = PLAYER) { stateMachine_ = &stateMachine; }
	EntityState* getState();

	bool isFacingRight() { return facingRight_; }
	void setFacingRight(bool facingRight) { facingRight_ = facingRight; }

private:
	EntityStateMachine* stateMachine_;
	bool facingRight_;
};

#include "EntityStateMachine.hpp"
#include "EntityState.hpp"*/

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