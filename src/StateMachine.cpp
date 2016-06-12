// #include "../include/StateMachine.hpp"
// #include "../include/GameState.hpp"
// #include "../include/LevelEditorState.hpp"
// #include "../include/MainMenuState.hpp"

// StateMachine::StateMachine()
// {

// }

// StateMachine::~StateMachine()
// {
// 	delete state_;
// }

// void StateMachine::create()
// {
// 	// state_ = new GameState();
// 	// state_ = new LevelEditorState();
// 	state_ = new MainMenuState();
// 	state_->create(*this);
// }

// void StateMachine::update(float dt)
// {
// 	state_->update(dt);
// }

// void StateMachine::render()
// {
// 	state_->render();
// }

// void StateMachine::changeState(IState& state)
// {
// 	delete state_;
// 	state_ = &state;
// 	state_->create(*this);
// }

// void StateMachine::handle(StateEventEnum& event)
// {
// 	state_->handle(event);
// }

// IState* StateMachine::getState()
// {
// 	return state_;
// }

// void StateMachine::setState(IState& state)
// {
// 	state_ = &state;
// }
