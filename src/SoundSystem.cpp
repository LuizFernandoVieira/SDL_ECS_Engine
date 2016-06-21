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

	//Percorrimento externo - Todas as entidades
	for (auto& sfx : sound){
		/*
		VERIFICAÇÃO ORIGINAL
		if (stateComp[sfx.first]->state_ != oldState[sfx.first]->state_){

			std::cout << "[Sound Message] State Changed to: " << stateComp[sfx.first]->state_ << std::endl;
			sfx.second->getSound(stateComp[sfx.first]->state_).Play();
		}
		*/

		/*ALERTA DE GAMBIARRA*/
		if ((int) stateComp[sfx.first]->state_ != sfx.second->lastState){
			// std::cout << "[Sound Message] State Changed to: " << stateComp[sfx.first]->state_ << std::endl;
			sfx.second->Play(stateComp[sfx.first]->state_);
			sfx.second->lastState = stateComp[sfx.first]->state_;
			/*
			sfx.second->getSound(stateComp[sfx.first]->state_).Play();
			sfx.second->lastState = stateComp[sfx.first]->state_;
			*/

			/*	Quando a verificação original estiver funcionando:
					1. Fazer update utilizá-la
					2. Descartar variável soundComponent.lastState 	("SoundComponent.hpp")
					2. Atualizar construtor de SoundComponent		("SoundComponent.hpp")
			*/
		}
	}
}
