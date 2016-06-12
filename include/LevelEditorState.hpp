#ifndef LEVELEDITORSTATE_HPP
#define LEVELEDITORSTATE_HPP

#include "IState.hpp"
#include "Panel.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"
#include "CollisionMap.hpp"
#include "ObjectMap.hpp"
#include "TileSetAndObjectsPanel.hpp"

#include <vector>

class TilesPanel;

class LevelEditorState: public IState
{
public:
	LevelEditorState();
	~LevelEditorState();

	void initGUI();

	void update(float dt);
	void render();

	void pause();
	void resume();

	enum Tools {
		ADD,
		SELECT,
		DELETE
	};
private:
	Rect getPanelRect(Rect& parent, Rect& proportions);

	TileSet* tileSet_;
	TileMap* tileMap_;
	CollisionMap* collisionMap_;
	ObjectMap* objectMap_;
	Panel mainPanel_;

	std::vector<Button*> tileButtons_;

	Button* addTilesBtn_;
	Button* selectTilesBtn_;
	Button* deleteTilesBtn_;

	std::vector<Button*> layerButtons_;
	std::vector<Button*> collisionButtons_;

	int selectedTile_;
	int selectedLayer_;
	TileSetAndObjectsPanel::Tab* selectedTab_;
	int selectedCollision_;
	Tools selectedTool_;
	int selectedObject_;

	TileSetAndObjectsPanel* tileSetAndObjectsPanel_;
};

// void tileBtnExecute(IState* state);


#endif
