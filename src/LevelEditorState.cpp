#include "../include/LevelEditorState.hpp"

void LevelEditorState::create(StateMachine& stateMachine)
{
	setStateMachine(stateMachine);
	firstLevelEditor_	= new FirstLevelEditor(*this);
	firstLevelEditor_->create();
}

void LevelEditorState::update(float dt)
{
	firstLevelEditor_->update(dt);
}

void LevelEditorState::render()
{
	firstLevelEditor_->render();
}

void LevelEditorState::handle(StateEventEnum& event)
{

}