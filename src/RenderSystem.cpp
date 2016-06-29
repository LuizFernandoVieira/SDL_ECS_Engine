#include "../include/RenderSystem.hpp"
#include "../include/Vec2.hpp"
#include "../include/Camera.hpp"
#include "../include/TransformComponent.hpp"
#include "../include/StateComponent.hpp"
#include "../include/RenderComponent.hpp"

RenderSystem::RenderSystem()
{
}


void RenderSystem::update(float dt, GameState& gameState)
{
	std::map<int, StateComponent*> oldState = gameState.oldState_;
	std::map<int, StateComponent*> stateComp = gameState.mapState_;
	std::map<int, std::map<int, RenderComponent*>> renderComp = gameState.mapRender_;

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

void RenderSystem::render(int layer, GameState& gameState)
{
	std::map<int, TransformComponent*> transfComp = gameState.mapTransform_;
	std::map<int, StateComponent*> stateComp = gameState.mapState_;
	std::map<int, RenderComponent*> renderComp = gameState.mapRender_[layer];

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
