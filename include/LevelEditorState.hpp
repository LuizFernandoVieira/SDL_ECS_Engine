#ifndef LEVELEDITORSTATE_HPP
#define LEVELEDITORSTATE_HPP

#include "State.hpp"
#include "StateMachine.hpp"
#include "StateEventEnum.hpp"
#include "FirstLevelEditor.hpp"

class LevelEditorState: public State
{
public:
	void create(StateMachine& stateMachine);
	void update(float dt);
	void render();
	void handle(StateEventEnum& event);
private:
	FirstLevelEditor* firstLevelEditor_;	
};

#endif