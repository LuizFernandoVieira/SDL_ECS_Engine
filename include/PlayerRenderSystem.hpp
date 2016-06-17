#ifndef PLAYERRENDERSYSTEM_HPP
#define PLAYERRENDERSYSTEM_HPP

#include <map>

#include "System.hpp"
#include "TransformComponent.hpp"
#include "StateComponent.hpp"
#include "RenderComponent.hpp"

class PlayerRenderSystem : public System
{
public:
	PlayerRenderSystem();
	void update(
		float dt,
		TransformComponent* transfComp,
		PlayerStateComponent* oldState,
		PlayerStateComponent* stateComp,
		PlayerRenderComponent* renderComp
	);
	void render(
		TransformComponent* transfComp,
		PlayerStateComponent* stateComp,
		PlayerRenderComponent* renderComp
	);
};

#endif