#ifndef ISTATE_HPP
#define ISTATE_HPP

#include "StateMachine.hpp"
#include "StateEventEnum.hpp"

class IState
{
public:
	virtual ~IState() {}
	virtual void create(StateMachine& stateMachine) = 0;
	virtual void update(float dt) = 0;
	virtual void render() = 0;
	virtual void handle(StateEventEnum& event) = 0;
};

#endif