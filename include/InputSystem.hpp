#ifndef INPUTSYSTEM_HPP
#define INPUTSYSTEM_HPP

#include <map>

#include "Rect.hpp"
#include "System.hpp"
#include "GameState.hpp"

class InputSystem : public System
{
public:
	InputSystem();
	void update(float dt, GameState& gameState);
};

#endif
