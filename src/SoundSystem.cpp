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
		//std::cout << "Current State: " << stateComp[sfx.first]->state_ << std::endl;
		//std::cout << "Old State: " << oldState[sfx.first]->state_ << std::endl;
		if (oldState[sfx.first]->state_ ==  stateComp[sfx.first]->state_)
			std::cout << "[EQUAL STATES] - Current State: " << oldState[sfx.first]->state_ << "// New State: " << stateComp[sfx.first]->state_ << std::endl;
		else std::cout << "[CHANGE DETECTED] - Current State: " << oldState[sfx.first]->state_ << "// New State: " << stateComp[sfx.first]->state_ << std::endl;

		if (stateComp[sfx.first]->state_ != oldState[sfx.first]->state_){

			std::cout << "[Render Message] State Changed to: " << stateComp[sfx.first]->state_ << std::endl;
			sfx.second->getSound(stateComp[sfx.first]->state_).Play();
		}
	}
		
/*		
	código de render
		if (stateComp[sfx.first]->state_ != oldState[sfx.first]->state_)
			{
				sfx.second->getSprite(stateComp[sfx.first]->state_).setFrame(0);
			}
			sfx.second->getSprite(stateComp[sfx.first]->state_).Play();
*/
/*
		//actorSound = sound[sfx.first];
		if (sound[sfx.first] != nullptr)
		{
			//Obtenção de primeiro elemento
			current_sfx = sound[sfx.first]->audioQueue.top();

			//current_sfx.Open(sound[sfx.first]->audioQueue.top())
			while (current_sfx.IsOpen()){

			//Execução de som
			//Mix_PlayChannel(-1, current_sfx, -1);
			current_sfx.Play();


			//Iteração (Pop + próximo elemento)
			sound[sfx.first]->audioQueue.pop();
			current_sfx = sound[sfx.first]->audioQueue.top();
			}
		}
	}
	*/
}


/*
		// ------------------------------------------------------------------------------------------------------------

		if (speed[phys.first]->speed_.y() < 0)
		{
			// TA PULANDO
			// Agora sim gravidade funciona como uma aceleracao (desaceleracao do pulo nesse caso)
			speed[phys.first]->speed_ += Vec2(0, Resources::GRAVITY * phys.second->gravityScale_ * dt * 4);
		}
		else
		{
			// TA CAINDO (A MENOS QUE ESTEJA COLIDINDO)
			speed[phys.first]->speed_.y(Resources::GRAVITY * phys.second->gravityScale_);
			state[phys.first]->state_ = State::FALLING;
		}
*/



/*
#include "../include/GravitySystem.hpp"
#include "../include/Resources.hpp"

GravitySystem::GravitySystem()
{

}

void GravitySystem::update( 
	float dt,
	std::map<int, SpeedComponent*> speed,
	std::map<int, PhysicsComponent*> physics,
	std::map<int, StateComponent*> state)
{
	for (auto& phys : physics)
	{
		if (speed[phys.first]->speed_.y() < 0)
		{
			// TA PULANDO
			// Agora sim gravidade funciona como uma aceleracao (desaceleracao do pulo nesse caso)
			speed[phys.first]->speed_ += Vec2(0, Resources::GRAVITY * phys.second->gravityScale_ * dt * 4);
		}
		else
		{
			// TA CAINDO (A MENOS QUE ESTEJA COLIDINDO)
			speed[phys.first]->speed_.y(Resources::GRAVITY * phys.second->gravityScale_);
			state[phys.first]->state_ = State::FALLING;
		}
	}
}

*/