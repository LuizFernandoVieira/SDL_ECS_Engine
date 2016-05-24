#include "../include/RenderSystem.hpp"

#include <iostream>

RenderSystem::RenderSystem()
{
}

void RenderSystem::render(std::map<int, TransformComponent*> tc,
	std::map<int, RenderComponent*> rc)
{
	for(auto it = rc.begin(); it != rc.end(); ++it) {
		Rect tcRect = tc[it->first]->rect_;
		it->second->getSprite()->render(
			tcRect.x(),
			tcRect.y(),
			0
		);
	}
}