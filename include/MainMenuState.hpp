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
	StaticSprite bg_;

	Sprite btnPlay_;
	Rect btnPlayPos_;
	Text btnPlayText_;

	Sprite btnMapEditor_;
	Rect btnMapEditorPos_;
	Text btnMapEditorText_;
};

#endif
