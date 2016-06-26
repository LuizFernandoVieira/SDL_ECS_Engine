#include "../include/RenderSystem.hpp"
#include "../include/Vec2.hpp"
#include "../include/Camera.hpp"
#include <iostream>

RenderSystem::RenderSystem()
{
}


void RenderSystem::update(
	float dt,
	std::map<int, StateComponent*> oldState,
	std::map<int, StateComponent*> stateComp,
	std::map<int, std::map<int, RenderComponent*>> renderComp)
{
	for (int i = 0; i < 4; i++)
	{
		for(auto& render : renderComp[i])
		{
			if (stateComp[render.first]->state_ != oldState[render.first]->state_)
			{
				render.second->getSprite(stateComp[render.first]->state_).setFrame(0);
			}
			render.second->getSprite(stateComp[render.first]->state_).update(dt);
		}
	}
}

void RenderSystem::render(
	int layer,
	std::map<int, TransformComponent*> transfComp,
	std::map<int, StateComponent*> stateComp,
	std::map<int, RenderComponent*> renderComp)
{
	Vec2 layerSpeed(0,0);
	switch (layer)
	{
		case 0:
			layerSpeed = Camera::pos_ * -0.5;
			break;
		case 4:
			layerSpeed = Camera::pos_ * 0.5;
			break;
		case 5:
			layerSpeed = Camera::pos_ * 0.75;
			break;
		default:
			break;
	}
	
	for(auto& render : renderComp)
	{
		Rect transform = transfComp[render.first]->rect_;
		render.second->getSprite(stateComp[render.first]->state_).setScaleX(transfComp[render.first]->scale_.x());
		render.second->getSprite(stateComp[render.first]->state_).setScaleY(transfComp[render.first]->scale_.y());
		render.second->getSprite(stateComp[render.first]->state_).render(
			transform.x() + layerSpeed.x(),
			transform.y() + layerSpeed.y(),
			transfComp[render.first]->rotation_,
			!stateComp[render.first]->facingRight_ // flip se nao ta virado pra direita
		);
	}
}
