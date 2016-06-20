#include "../include/GravitySystem.hpp"
#include "../include/Resources.hpp"

#ifdef __APPLE__
	#include <SDL2/SDL.h>
	#include <SDL2_mixer/SDL_mixer.h>
#else
	#include "SDL.h"
	#include "SDL_mixer.h"
#endif

#include "../include/SoundSystem.hpp"

SoundSystem::SoundSystem(){
}

void SoundSystem::update(
	std::map<int, StateComponent*> oldState,
	std::map<int, StateComponent*> stateComp,
	std::map<int, SoundComponent*> sound)
{


	//	Mix_Chunk* current_sfx = nullptr;
	//SoundComponent* actorSound = sound[sfx.first];

	//Percorrimento externo - Todas as entidades
	for (auto& sfx : sound){

		if (stateComp[sfx.first]->state_ != oldState[sfx.first]->state_){

			// std::cout << "[Render Message] State Changed to: " << stateComp[sfx.first]->state_ << std::endl;
			sfx.second->getSound(stateComp[sfx.first]->state_).Play();
		}
	}
}
