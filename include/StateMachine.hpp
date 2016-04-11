#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include "StateEventEnum.hpp"

class State;

class StateMachine
{
public:
	StateMachine();
	~StateMachine();
	void create();
	void update(float dt);
	void render();
	void changeState(State& state);
	void handle(StateEventEnum& event);
	State* getState();
	void setState(State& state);
private:
	State* state_;
};

#include "State.hpp"

#endif