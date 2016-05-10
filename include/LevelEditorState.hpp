#ifndef LEVELEDITORSTATE_HPP
#define LEVELEDITORSTATE_HPP

#include "State.hpp"
#include "StateMachine.hpp"
#include "StateEventEnum.hpp"
#include "Panel.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"

class TilesPanel;

class LevelEditorState: public State
{
public:
	LevelEditorState();
	~LevelEditorState();
	void create(StateMachine& stateMachine);
	void initGUI();
	void update(float dt);
	void render();
	void handle(StateEventEnum& event);
	
	enum Tools {
		ADD,
		SELECT,
		DELETE
	};
private:
	Rect getPanelRect(Rect& parent, Rect& proportions);

	TileSet* tileSet_;
	TileMap* tileMap_;
	Panel mainPanel_;

	std::vector<Button*> tileButtons_;

	Button* addTilesBtn_;
	Button* selectTilesBtn_;
	Button* deleteTilesBtn_;

	int selectedTile_;
	Tools selectedTool_;
};

void tileBtnExecute(State* state);


#endif