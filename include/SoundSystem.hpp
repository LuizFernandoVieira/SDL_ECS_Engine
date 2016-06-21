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
};

#endif