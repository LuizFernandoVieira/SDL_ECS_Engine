#ifndef SOUNDSYSTEM_HPP
#define SOUNDSYSTEM_HPP

#include <map>
#include <unordered_map>

#include "System.hpp"
#include "GameState.hpp"

class SoundSystem : public System{

	public:
	SoundSystem();

	void update(float dt, GameState& gameState);
};

#endif