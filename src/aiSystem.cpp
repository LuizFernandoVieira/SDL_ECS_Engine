#include "../include/AISystem.hpp"
#include "../include/AIComponent.hpp"

#define AI_DEBUG true

AISystem::AISystem()
{
	//trigger_table.push_back((verification) &AlwaysTrue);
}

void AISystem::update(float dt, GameState& gameState)
{
	
	std::map<int, AIComponent*> ai_comp 		= gameState.mapAI_;
	

	//std::cout << "updating AI" << std::endl;
	bool move = false;
	//Processamento de IAs
	for (auto& ai : ai_comp){

		//Update de cooldown :: Mudara para update em um vetor/hash table, contendo cooldowns individuais
		ai.second->current_action_timer.update(dt);
		auto& current_state = ai.second->states[ai.second->state_index];

		//Loop de verificação de condições
		for (auto& trigger : current_state.triggers){
			switch(trigger.first){
				//trigger agora contém o código equivalente à verificação necessária para a mudança de estado definida

				//Caso: Esperar Cooldown
				case 0:
					move = true;
					break;

				//Caso: Idle
				case 1:
					//move = true;
					move = ((int) current_state.state == 0);
					break;

				default:
					ai.second->state_index = trigger.second;
					break;
			}


			//AI improvement: mover timer para estados individuais
			if (move && ai.second->current_action_timer.get() >= current_state.hold){
				ai.second->state_index = trigger.second;
				ai.second->current_action_timer.restart();	
			}
		}

	if (AI_DEBUG){ ai.second->PrintCurrentState();}
	}


/*
	//---------------------------------------------------------------------------
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
			if (state[phys.first]->state_ != State::ZIPLINE)
			{
				speed[phys.first]->speed_.y(Resources::GRAVITY * phys.second->gravityScale_);
				if (state[phys.first]->state_ != State::GRAPPLE && state[phys.first]->state_ != State::ATTACKING)
				{
					state[phys.first]->state_ = State::FALLING;
				}
			}
		}
	}
	*/
}