#ifndef MAINMENUSTATE_HPP
#define MAINMENUSTATE_HPP

#include "IState.hpp"
#include "StaticSprite.hpp"
#include "Text.hpp"

class MainMenuState : public IState
{
public:
	MainMenuState();
	~MainMenuState();

	void update(float dt);
	void render();

	void pause();
	void resume();

private:
	Text info_;
	StaticSprite bg_;
};


#endif