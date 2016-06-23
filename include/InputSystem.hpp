#ifndef INPUTSYSTEM_HPP
#define INPUTSYSTEM_HPP

#include <map>

#include "Rect.hpp"
#include "System.hpp"
#include "SpeedComponent.hpp"
#include "StateComponent.hpp"
#include "PhysicsComponent.hpp"
#include "ColliderComponent.hpp"

class InputSystem : public System
{
public:
	InputSystem();
	void update(
		PlayerStateComponent* stateComp,
		SpeedComponent* speedComp,
		PhysicsComponent* physicsComp,
		ColliderComponent* colComp
	);
};

#endif