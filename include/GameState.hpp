#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "State.hpp"
#include "StateMachine.hpp"
#include "StateEventEnum.hpp"
#include "FirstLevel.hpp"

class GameState: public State
{
public:
	GameState();
	~GameState();
	void create(StateMachine& stateMachine);
	void update(float dt);
	void render();
	void handle(StateEventEnum& event);
private:
	FirstLevel* firstLevel_;
};

#endif