#ifndef FIRSTLEVELEDITOR_HPP
#define FIRSTLEVELEDITOR_HPP

#include <map>
#include <vector>

#include "ILevel.hpp"
#include "State.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"
// #include "StateSystem.hpp"
#include "RenderSystem.hpp"
#include "LevelEditorSystem.hpp"

class FirstLevelEditor : public ILevel
{
public:
	FirstLevelEditor(State& state);
	~FirstLevelEditor();
	void create();
	void update(float dt);
	void render();
private:
	void createGod();
	State* state_;
	TileSet* tileSet_;
	TileMap* tileMap_;
	unsigned int god_;
	static unsigned int nextId_;
	std::map<int, TransformComponent*> mapTransform_;
	// std::map<int, StateComponent*> 	mapState_;
	std::map<int, RenderComponent*> mapRender_;
	// StateSystem* stateSystem_;
	RenderSystem* renderSystem_;
	LevelEditorSystem* editorSystem_;
};

#endif