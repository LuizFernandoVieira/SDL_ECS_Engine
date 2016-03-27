#ifndef FIRSTLEVELEDITOR_HPP
#define FIRSTLEVELEDITOR_HPP

#include "ILevel.hpp"
#include "State.hpp"
#include "InputHandler.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"
#include "God.hpp"

class FirstLevelEditor : public ILevel
{
public:
	FirstLevelEditor(State& state);
	~FirstLevelEditor();
	void create();
	void update(float dt);
	void render();
private:
	State* state_;
	InputHandler* inputHandler_;
	TileSet* tileSet_;
	TileMap* tileMap_;
	God* god_;
};

#endif