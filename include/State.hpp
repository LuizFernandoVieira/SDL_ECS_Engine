#ifndef STATE_HPP
#define STATE_HPP

#include "IState.hpp"
#include "StateMachine.hpp"

class State: public IState
{
public:
	void create(StateMachine& stateMachine);
	void update(float dt);
	void render();
	bool quitRequested();
	StateMachine* getStateMachine();
	void setStateMachine(StateMachine& stateMachine);
	bool getQuit() { return quit; }
	void setQuit(bool q) { quit = q; } 
protected:
	bool quit;
private:
	StateMachine* stateMachine_;
};

#endif