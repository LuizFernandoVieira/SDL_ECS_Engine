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
			/*
			for (auto& assets : component_sfx){

			}
			*/
		}
	~SoundComponent() { /*delete rect_;*/ }


	Sound& getSound(State state) {
		return assets[state];
		/*
		if (assets.find(state) != assets.end())
			return assets[state];
		else return NULL;
		*/
	}



	//std::stack<Sound>	audioQueue;

	//TESTE :: 'int' está na verdade recebendo um enum e castando. Caso não funcione:
		//OPÇÃO 1: Passar bagunça Hash de render component para state component, e usar a mesma hash
		//OPÇÃO 2: Copiar bagunça Hash de render component para cá e rezar

	std::unordered_map<State, Sound>	assets;
	void addSound(State state, Sound sound)
		{ assets.emplace(state, sound); }

};

#endif