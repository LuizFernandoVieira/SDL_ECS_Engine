#ifndef RENDERSYSTEM_HPP
#define RENDERSYSTEM_HPP

#include <map>

#include "System.hpp"
#include "TransformComponent.hpp"
#include "RenderComponent.hpp"

class RenderSystem : public System
{
public:
	RenderSystem();
	void update(
		std::map<int, TransformComponent*> tc,
		std::map<int, RenderComponent*> rc
	);
};

#endif