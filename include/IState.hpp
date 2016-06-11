#ifndef STATE_HPP
#define STATE_HPP

#include "StateMachine.hpp"

class IState
{
public:
	virtual ~IState() {}
	virtual void create(StateMachine& stateMachine) {}
	virtual void update(float dt) = 0;
	virtual void render() = 0;
	virtual void handle (StateEventEnum& event) = 0;
	bool quitRequested();
	StateMachine* getStateMachine();
	void setStateMachine(StateMachine& stateMachine);
	bool getQuit() { return quit; }
	void setQuit(bool q) { quit = q; } 
protected:
	bool quit;
	StateMachine* stateMachine_;
};

#endif