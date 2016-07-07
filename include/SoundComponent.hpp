#ifndef SoundComponent_HPP
#define SoundComponent_HPP

#ifdef __APPLE__
	#include <SDL2/SDL.h>
	#include <SDL2_mixer/SDL_mixer.h>
#else
	#include "SDL.h"
	#include "SDL_mixer.h"
#endif

#include "Sound.hpp"
#include "Component.hpp"
#include "StateComponent.hpp"
#include <stack>

class SoundComponent : public Component
{

public:
	SoundComponent() { lastState = 0; }
	~SoundComponent() {assets.clear();}


	Sound& getSound(State state) { return assets[state]; }

	void Play(State state) {assets[state].Play();}

	void addSound(State state, Sound sound) { assets.emplace(state, sound);}

	int lastState;

	std::unordered_map<State, Sound>	assets;

};

#endif
