#ifndef EDITORSELECTSTATE_HPP
#define EDITORSELECTSTATE_HPP

#include <vector>

#include "IState.hpp"
#include "StaticSprite.hpp"
#include "Text.hpp"
#include "Rect.hpp"

class EditorSelectState : public IState
{
public:
	EditorSelectState();
	~EditorSelectState();

	void update(float dt);
	void render();

	void pause();
	void resume();

	enum Mode { INIT, NEW_MAP, EDIT_MAP };

private:
	void accept();

	StaticSprite bg_;

	Mode mode;

	Sprite btnNewMap;
	Rect btnNewMapPos;
	Text btnNewMapText;

	Sprite btnEditMap;
	Rect btnEditMapPos;
	Text btnEditMapText;

	Sprite btnAccept;
	Rect btnAcceptPos;
	Text btnAcceptText;

	Sprite btnReturn;
	Rect btnReturnPos;
	Text btnReturnText;

	std::vector<Text*> textLabels;
	std::vector<Text*> textAreas;

	int selectedTextArea;
};

#endif
