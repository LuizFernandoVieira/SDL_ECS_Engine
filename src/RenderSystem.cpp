#include "../include/RenderSystem.hpp"

#include <iostream>

RenderSystem::RenderSystem()
{
}


void RenderSystem::update(
	float dt,
	std::map<int, StateComponent*> oldState,
	std::map<int, StateComponent*> stateComp,
	std::map<int, RenderComponent*> renderComp)
{
	for(auto& render : renderComp)
	{
		if (stateComp[render.first]->state_ != oldState[render.first]->state_)
		{
			render.second->getSprite(stateComp[render.first]->state_).setFrame(0);
		}
		render.second->getSprite(stateComp[render.first]->state_).update(dt);
	}
}

void RenderSystem::render(
	std::map<int, TransformComponent*> transfComp,
	std::map<int, StateComponent*> stateComp,
	std::map<int, RenderComponent*> renderComp)
{
	for(auto& render : renderComp)
	{
		Rect transform = transfComp[render.first]->rect_;
		render.second->getSprite(stateComp[render.first]->state_).render(
			transform.x(),
			transform.y(),
			0,
			!stateComp[render.first]->facingRight_ // flip se nao ta virado pra direita
		);
	}
}
