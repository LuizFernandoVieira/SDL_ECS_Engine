#ifndef TILEMAPPANEL_HPP
#define TILEMAPPANEL_HPP

#include <string>
#include <iostream>
#include <vector>

#include "Rect.hpp"
#include "Vec2.hpp"
#include "Sprite.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"
#include "CollisionMap.hpp"
#include "ObjectMap.hpp"
#include "Panel.hpp"
#include "LevelEditorState.hpp"

struct Object
{
	int id;
	int layer;
	Rect pos;
	Sprite sprite;
};

class TileMapPanel : public Panel
{
public:
	TileMapPanel(TileSet& tileSet, TileMap& tileMap, CollisionMap& collisionMap, ObjectMap& objectMap, Rect rect, std::string imgPath, int& selectedTile, int& selectedLayer, int& selectedCollision, int* selectedTab, int& selectedObject, LevelEditorState::Tools& selectedTool);
	~TileMapPanel();
	void update();
	void render();

private:
	void placeTile(int x, int y);
	void deleteTile(int x, int y);
	void placeCollisionTile(int x, int y);
	void deleteCollisionTile(int x, int y);
	void placeObject(int x, int y, int layer);
	void deleteObject(int x, int y, int layer);

	void loadObjects();

	TileSet* tileSet_;
	TileMap* tileMap_;
	ObjectMap* objectMap_;
	CollisionMap* collisionMap_;

	Rect cursorPos_;
	Sprite cursorBg_;

	Sprite* objectSp_;

	Vec2 firstDragClick_;
	Vec2 curDragClick_;

	int* selectedTile_;
	int* selectedLayer_;
	int* selectedCollision_;
	int* selectedTab_;
	int* selectedObject_;
	int previousSelectedObject_;

	LevelEditorState::Tools* selectedTool_;

	std::vector<Object> objects_;

	static int nextId;
};

#endif
