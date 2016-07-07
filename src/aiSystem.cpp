#include "../include/AISystem.hpp"
#include "../include/AIComponent.hpp"
#include "../include/Resources.hpp"

#include "../include/Text.hpp"

#define AI_PROCESSING_DISTANCE	(Resources::WINDOW_WIDTH / 2)
#define FOLLOW_TARGET 			gameState.player_
#define FOLLOW_DISTANCE 		50.0f
#define X_FOLLOW_DISTANCE 		20.0f

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
	for (auto& ai : aiComp)
		if( Distance(gameState.mapTransform_[ai.first]->rect_.getCenter(),
			gameState.mapTransform_[gameState.player_]->rect_.getCenter())
				< AI_PROCESSING_DISTANCE){

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
		float centerdist;
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
					centerdist = (colComp->hitbox_.w() + gameState.mapCollider_[FOLLOW_TARGET]->hurtbox_.w()) / 2;

					move = (centerdist < Distance( colComp->hitbox_.getCenter(),
								gameState.mapCollider_[FOLLOW_TARGET]->hurtbox_.getCenter()));
					break;

				//Caso: Perto Demais do Alvo
				case 3:
					centerdist = (colComp->hitbox_.w() + gameState.mapCollider_[FOLLOW_TARGET]->hurtbox_.w()) / 2;

					move = (centerdist > Distance( colComp->hitbox_.getCenter(),
								gameState.mapCollider_[FOLLOW_TARGET]->hurtbox_.getCenter()));
					break;

				//Caso: Abaixo do Alvo	
				case 4:
					move = (gameState.mapTransform_[FOLLOW_TARGET]->rect_.getCenter().y()
						> 	transComp->rect_.getCenter().y() + Resources::TILE_HEIGHT);
					break;					

				//Caso: Proximidade de ataque
				case 5:
					//move = Distance(ai.first, gameState.player_, FOLLOW_DISTANCE);
					move = (colComp->hitbox_.w() > Distance( transComp->rect_, 
								gameState.mapTransform_[FOLLOW_TARGET]->rect_));
					break;

				//Caso: Perto demais em X
				case 6:
					move = (X_FOLLOW_DISTANCE > abs(
						gameState.mapTransform_[FOLLOW_TARGET]->rect_.getCenter().x()
						- transComp->rect_.getCenter().x())); // && != FALLING
					break;


				//Caso: Longe demais em X
				case 7:
					move = (X_FOLLOW_DISTANCE < abs(
						gameState.mapTransform_[FOLLOW_TARGET]->rect_.getCenter().x()
						- transComp->rect_.getCenter().x())); // && != FALLING
					break;

				//Caso: Falso
				case 8:
					move = false;
					break;

				//Caso: Not-Airborne
				case 9:
					move = (gameState.mapState_[ai.first]->state_ != State::JUMPING); // && != FALLING
					break;

				//Caso: Player is Dead
				case 10:
					/* Verificação funciona */
					move = (gameState.mapState_[FOLLOW_TARGET]->state_ == State::DYING)
						|| (gameState.mapState_[FOLLOW_TARGET]->state_ == State::DEAD);
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
				goto verificationBreak;
			}
			//Não houve mudança de estado no frame
			else move = false; 
		}
		
	verificationBreak:


	if (Resources::DEBUG_AI){
		printf("Player State: %d\t || AI ", gameState.mapState_[FOLLOW_TARGET]->state_);
		ai.second->PrintCurrentState();
		printf("\t Distance: %.0f\t || Desired Distance: %.3f\n", Distance( transComp->rect_,	gameState.mapTransform_[FOLLOW_TARGET]->rect_), centerdist);
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
		};*/
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


			//ATTACKING
			case 4:
				if (move){
					stateComp->state_ = State::ATTACKING;
					colComp->hitbox_ = Rect( stateComp->facingRight_ ? 58 : -40, 30, 52, 48);
				}
				break;

			//FOLLOW
			case 9:
				if(	gameState.mapTransform_[gameState.player_]	->rect_.getCenter().x()
					> 	transComp 								->rect_.getCenter().x()){
					speedComp->speed_.x(Resources::PLAYER_WALK_SPEED / 1.25);
					stateComp->facingRight_ = true;
				}
				else{
					(speedComp->speed_.x(-Resources::PLAYER_WALK_SPEED / 1.25));
					stateComp->facingRight_ = false;
				}
				stateComp->state_ = State::WALKING;
				break;

			default:
				break;
		}
	}

/*
	if (AI_DEBUG)
		Show();
*/
}

/*
void aiSystem::Show(){
	usar text para printar estado corrente acima da cabeça da AI 
}
*/