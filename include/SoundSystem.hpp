#ifndef SOUNDSYSTEM_HPP
#define SOUNDSYSTEM_HPP

#include <map>
#include <unordered_map>

#include "Sound.hpp"
#include "System.hpp"
#include "SoundComponent.hpp"
#include "StateComponent.hpp"

class SoundSystem : public System{

	public:
	SoundSystem();

	void update(
		std::map<int, StateComponent*> oldState,
		std::map<int, StateComponent*> stateComp,
		std::map<int, SoundComponent*> speed);

	//Mix_Chunk* current_sfx;
	//Sound current_sfx;
};

#endif
/*
#ifndef GRAVITYSYSTEM_HPP
#define GRAVITYSYSTEM_HPP

#include <map>

#include "System.hpp"
#include "SpeedComponent.hpp"
#include "StateComponent.hpp"
#include "PhysicsComponent.hpp"

class GravitySystem : public System
{
public:
	GravitySystem();
	void update(
		float dt,
		std::map<int, SpeedComponent*> speed,
		std::map<int, PhysicsComponent*> physics,
		std::map<int, StateComponent*> state
	);
};

#endif
*/