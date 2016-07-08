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

	// std::cout << renderComp[2].size() << std::endl;
	for (int i = 0; i < 6; i++)
	{
		for(auto& render : renderComp[i])
		{
			if (render.first == 598)
				std::cout << stateComp[render.first]->state_ << std::endl;
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
		Sprite& sprite = render.second->getSprite(stateComp[render.first]->state_);
		sprite.setScaleX(transfComp[render.first]->scale_.x());
		sprite.setScaleY(transfComp[render.first]->scale_.y());
		sprite.render(
			transform.getBase().x() - (sprite.getWidth() / 2) + layerSpeed.x(),
			transform.getBase().y() - sprite.getHeight() + layerSpeed.y(),
			transfComp[render.first]->rotation_,
			!stateComp[render.first]->facingRight_ // flip se nao ta virado pra direita
		);
	}
}
