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
	SoundComponent()
		{
			lastState = 0;
			/*
			for (auto& assets : component_sfx){

			}
			*/
		}
	~SoundComponent() {assets.clear();}


	Sound& getSound(State state) {
		//if (assets[state] == nullptr)
			//std::cout << "getSound returned nullptr" << std::endl;
		return assets[state];
		/*
		if (assets.find(state) != assets.end())
			return assets[state];
		else return NULL;
		*/
	}

	void Play(State state)
		{assets[state].Play();}


	
	void addSound(State state, Sound sound)
		{ assets.emplace(state, sound);}

	int lastState;
//private:
	std::unordered_map<State, Sound>	assets;

};

#endif