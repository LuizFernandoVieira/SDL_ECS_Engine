#include "../include/AISystem.hpp"
#include "../include/AIComponent.hpp"
#include "../include/Resources.hpp"

#define AI_DEBUG true

#define FOLLOW_DISTANCE 100.0f
#define FOLLOW_TARGET gameState.player_

AISystem::AISystem()
{
	//trigger_table.push_back((verification) &AlwaysTrue);
}

void AISystem::update(float dt, GameState& gameState)
{
	
	std::map<int, AIComponent*> aiComp	= gameState.mapAI_;

	StateComponent* stateComp;
	SpeedComponent* speedComp;
	PhysicsComponent* physicsComp;
	ColliderComponent* colComp;
	TransformComponent* transComp;


	bool move = false;
	//Processamento de IAs
	for (auto& ai : aiComp){

		stateComp 	= gameState.mapState_[ai.first];
		speedComp	= gameState.mapSpeed_[ai.first];
		physicsComp	= gameState.mapPhysics_[ai.first];
		colComp		= gameState.mapCollider_[ai.first];
		transComp	= gameState.mapTransform_[ai.first];

		//Update de Cooldown por estado
		for (auto& state : ai.second->states){
			state.action_timer.update(dt);
		}

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
						move = ((int) current_state.state == 0);
					break;


				//Caso: Longe Demais do Alvo
				case 2:
					//move = Distance(ai.first, gameState.player_, FOLLOW_DISTANCE);
					move = (FOLLOW_DISTANCE < Distance( transComp->rect_,
								gameState.mapTransform_[FOLLOW_TARGET]->rect_));

					/*
					move = (gameState.mapTransform_[gameState.player_]->rect_.getCenter().x() - 
							gameState.mapTransform_[ai.first]->			rect_.getCenter().x())
					*/
					break;

				//Caso: Perto Demais do Alvo
				case 3:
					//move = Distance(ai.first, gameState.player_, FOLLOW_DISTANCE);
					move = (FOLLOW_DISTANCE > Distance( transComp->rect_,
								gameState.mapTransform_[FOLLOW_TARGET]->rect_));
					break;

				//Caso: Abaixo do Alvo	
				case 4:
					move = (gameState.mapTransform_[gameState.player_]->rect_.getCenter().y()
						> 	gameState.mapTransform_[ai.first]->			rect_.getCenter().y() + Resources::TILE_HEIGHT);
					break;					

				//Ué
				default:
					move = false;
					break;
			}


				//Se movimento for válido
			if (move && current_state.action_timer.get() >= current_state.cooldown){				
				ai.second->state_index = trigger.second;
				current_state.action_timer.restart();	
			}

			//Não houve mudança de estado no frame
			else move = false; 
		}

	if (AI_DEBUG){
		ai.second->PrintCurrentState();
		printf("\t Distance: %.0f\n", Distance( transComp->rect_,	gameState.mapTransform_[FOLLOW_TARGET]->rect_));
	}




	//Consolidação da Ação
	switch ((int) ai.second->states[ai.second->state_index].state){
	/*
		enum EntityState
		{
			IDLE,		//0
			WALKING,	//1
			JUMPING,	//2
			FALLING,	//3
			ATTACKING,	//4
			GRAPPLE,	//5
			ZIPLINE,	//6
			SHOOT,		//7
			DEAD,		//8
			FOLLOW		//9
		};
	*/
			//IDLE
			case 0:				
				speedComp->speed_.y(0);
				speedComp->speed_.x(0);
				stateComp->state_ = State::IDLE;
				break;

			//WALK
			case 1:

				break;

			//JUMP
			case 2:
				if (move){
					speedComp->speed_.y(-Resources::PLAYER_JUMP_SPEED);
					stateComp->state_ = State::JUMPING;
				}
				break;

			//FOLLOW
			case 9:
				//if(transComp	= gameState.mapTransform_[ai.second->action_target])
				if(			gameState.mapTransform_[gameState.player_]->rect_.getCenter().x()
						> 	gameState.mapTransform_[ai.first]->			rect_.getCenter().x()){
					speedComp->speed_.x(Resources::PLAYER_WALK_SPEED / 1.25);
				}
				else{
					(speedComp->speed_.x(-Resources::PLAYER_WALK_SPEED / 1.25));
				}


				stateComp->state_ = State::WALKING;
				break;

			default:
				break;
		}
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