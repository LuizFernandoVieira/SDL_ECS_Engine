#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <map>

#include "System.hpp"
#include "TransformComponent.hpp"
#include "StateComponent.hpp"
#include "RenderComponent.hpp"

class RenderSystem : public System
{
public:
	RenderSystem();
	void update(
		float dt,
		std::map<int, StateComponent*> oldState,
		std::map<int, StateComponent*> stateComp,
		std::map<int, RenderComponent*> renderComp
	);
	void render(
		std::map<int, TransformComponent*> transfComp,
		std::map<int, StateComponent*> stateComp,
		std::map<int, RenderComponent*> renderComp
	);
};

#endif