#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include "StateEventEnum.hpp"

class IState;

class StateMachine
{
public:
	StateMachine();
	~StateMachine();
	void create();
	void update(float dt);
	void render();
	void changeState(IState& state);
	void handle(StateEventEnum& event);
	IState* getState();
	void setState(IState& state);
private:
	IState* state_;
};

#include "IState.hpp"

#endif