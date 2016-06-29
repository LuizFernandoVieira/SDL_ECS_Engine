#ifdef __APPLE__
	#include <SDL2/SDL.h>
	#include <SDL2_mixer/SDL_mixer.h>
#else
	#include "SDL.h"
	#include "SDL_mixer.h"
#endif

#include "../include/SoundSystem.hpp"
#include "../include/GravitySystem.hpp"
#include "../include/Resources.hpp"
#include "../include/Sound.hpp"
#include "../include/SoundComponent.hpp"
#include "../include/StateComponent.hpp"


SoundSystem::SoundSystem(){
}

void SoundSystem::update(float dt, GameState& gameState)
{
	// std::map<int, StateComponent*> oldState = gameState.oldState_;
	std::map<int, StateComponent*> stateComp = gameState.mapState_;
	std::map<int, SoundComponent*> sound = gameState.mapSound_;

	//Percorrimento externo - Todas as entidades
	for (auto& sfx : sound){

		/*ALERTA DE GAMBIARRA*/
		if ((int) stateComp[sfx.first]->state_ != sfx.second->lastState)
		{
			sfx.second->Play(stateComp[sfx.first]->state_);
			sfx.second->lastState = stateComp[sfx.first]->state_;

			/*	Quando a verificação original estiver funcionando:
					1. Fazer update utilizá-la
					2. Descartar variável soundComponent.lastState 	("SoundComponent.hpp")
					2. Atualizar construtor de SoundComponent		("SoundComponent.hpp")
			*/
		}
	}
}
