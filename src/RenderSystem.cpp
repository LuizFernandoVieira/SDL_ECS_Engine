#include "../include/RenderSystem.hpp"

#include <iostream>

RenderSystem::RenderSystem()
{
}


void RenderSystem::update(
	float dt,
	std::map<int, StateComponent*> stateComp,
	std::map<int, RenderComponent*> renderComp)
{
	for(auto& render : renderComp)
	{
		if (stateComp[render.first]->getStateMachine()->hasChanged())
		{
			render.second->setCurrentSprite( stateComp[render.first]->getState()->getName() );
			render.second->getCurrentSprite()->setFrame(0);
		}
		else
		{
			render.second->getCurrentSprite()->update(dt);
		}
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
		render.second->getCurrentSprite()->render(
			transform.x(),
			transform.y(),
			0,
			!stateComp[render.first]->isFacingRight() // flip se nao ta virado pra direita
		);
	}
}