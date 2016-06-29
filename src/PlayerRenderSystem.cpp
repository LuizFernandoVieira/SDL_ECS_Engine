#include "../include/PlayerRenderSystem.hpp"
#include "../include/TransformComponent.hpp"
#include "../include/StateComponent.hpp"
#include "../include/RenderComponent.hpp"


PlayerRenderSystem::PlayerRenderSystem()
{
}


void PlayerRenderSystem::update(float dt, GameState& gameState)
{
	PlayerStateComponent* oldState = (PlayerStateComponent*)gameState.oldState_[gameState.player_];
	PlayerStateComponent* stateComp = (PlayerStateComponent*)gameState.mapState_[gameState.player_];
	PlayerRenderComponent& renderComp = gameState.playerRenderComponent_;

	SpriteKey spriteKey;
	spriteKey.state = stateComp->state_;
	spriteKey.umbrellaState = stateComp->umbrellaState_;
	spriteKey.umbrellaDirection = stateComp->umbrellaDirection_;

	if (stateComp->state_ != oldState->state_ || 
		stateComp->umbrellaState_ != oldState->umbrellaState_ || 
		stateComp->umbrellaDirection_ != oldState->umbrellaDirection_)
	{
		renderComp.getSprite(spriteKey).setFrame(0);
	}
	renderComp.getSprite(spriteKey).update(dt);
}

void PlayerRenderSystem::render(GameState& gameState)
{
	TransformComponent* transfComp = gameState.mapTransform_[gameState.player_];
	PlayerStateComponent* stateComp = (PlayerStateComponent*)gameState.mapState_[gameState.player_];
	PlayerRenderComponent& renderComp = gameState.playerRenderComponent_;

	SpriteKey spriteKey;
	spriteKey.state = stateComp->state_;
	spriteKey.umbrellaState = stateComp->umbrellaState_;
	spriteKey.umbrellaDirection = stateComp->umbrellaDirection_;

	Rect transform = transfComp->rect_;
	renderComp.getSprite(spriteKey).setScaleX(transfComp->scale_.x());
	renderComp.getSprite(spriteKey).setScaleY(transfComp->scale_.y());
	renderComp.getSprite(spriteKey).render(
		transform.x(),
		transform.y(),
		transfComp->rotation_,
		!stateComp->facingRight_ // flip se nao ta virado pra direita
	);
}
