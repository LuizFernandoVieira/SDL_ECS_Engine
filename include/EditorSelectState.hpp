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

	Sprite btnEditMap;
	Rect btnEditMapPos;

	Sprite btnAccept;
	Rect btnAcceptPos;

	Sprite btnReturn;
	Rect btnReturnPos;

	std::vector<Text*> textLabels;
	std::vector<Text*> textAreas;

	int selectedTextArea;
};

#endif
