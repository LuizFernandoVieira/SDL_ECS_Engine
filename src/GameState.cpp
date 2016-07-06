#ifdef __APPLE__
	#include <SDL2/SDL.h>
#else
	#include "SDL.h"
#endif
#include <vector>
#include <unordered_map>
#include <exception>

#include "../include/Game.hpp"
#include "../include/GameState.hpp"
#include "../include/Camera.hpp"
#include "../include/InputHandler.hpp"

#include "../include/StaticSprite.hpp"

#include "../include/InputSystem.hpp"
#include "../include/PlayerRenderSystem.hpp"
#include "../include/RenderSystem.hpp"
#include "../include/MoveSystem.hpp"
#include "../include/GravitySystem.hpp"
#include "../include/CollisionSystem.hpp"
#include "../include/HealthSystem.hpp"
#include "../include/SoundSystem.hpp"
#include "../include/AttackSystem.hpp"
#include "../include/AISystem.hpp"
#include "../include/ParticleEmitterSystem.hpp"

#define LEVEL_1_FILE "../map/FaseUm.xml"
	//Ideia: Fazer um vetor estático de strings em Resources, lendo dinamicamente de config.xml as fases


unsigned int GameState::nextId_ = 0;
std::map<int, std::map<int, RenderComponent*>> GameState::mapRender_;

GameState::GameState()
: music()
	//testando componente de música, não há necessidade de se carregar um arquivo
	//A própria music está carregando um arquivo teste
{
	StaticSprite loadScreen("../img/loading.png");
	loadScreen.render(0,0);
	SDL_RenderPresent(Game::getInstance().getRenderer());
	level_ = nullptr;

	try{
		mapRender_[0] = std::map<int, RenderComponent*>();
		mapRender_[1] = std::map<int, RenderComponent*>();
		mapRender_[2] = std::map<int, RenderComponent*>();
		mapRender_[3] = std::map<int, RenderComponent*>();
		mapRender_[4] = std::map<int, RenderComponent*>();
		mapRender_[5] = std::map<int, RenderComponent*>();

		loadLevel(LEVEL_1_FILE);

		systems_.emplace_back(new InputSystem());
		systems_.emplace_back(new GravitySystem());
		systems_.emplace_back(new MoveSystem());
		systems_.emplace_back(new AttackSystem());
		systems_.emplace_back(new CollisionSystem());
		systems_.emplace_back(new HealthSystem());
		systems_.emplace_back(new RenderSystem());
		systems_.emplace_back(new PlayerRenderSystem());
		systems_.emplace_back(new SoundSystem());
		systems_.emplace_back(new AISystem());
		//systems_.emplace_back(new ParticleEmitterSystem());

		//createParticleEmitter();

		Camera::follow(mapTransform_[player_]);
	}
	catch (std::exception& e)
	{
		std::cout << "DEU MERDA: " << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "DEU MUITA MERDA" << std::endl;
	}

}

GameState::~GameState()
{
	delete level_;
	nextId_ = 0;

	mapTransform_.clear();
	mapState_.clear();
	mapPhysics_.clear();
	mapCollider_.clear();
	mapSpeed_.clear();
	mapEmitter_.clear();
	mapTimer_.clear();
	mapZipline_.clear();
	mapSound_.clear();
	mapHealth_.clear();
	mapWind_.clear();
	oldTransform_.clear();
	oldState_.clear();

	mapRender_[0].clear();
	mapRender_[1].clear();
	mapRender_[2].clear();
	mapRender_[3].clear();
	mapRender_[4].clear();
	mapRender_[5].clear();

	systems_.clear();

	Camera::unfollow();
	Camera::pos_ = Vec2(0,0);
}


CollisionMap& GameState::getCollisionMap()
{
	return level_->getCollisionMap();
}


void GameState::update(float dt)
{
	InputHandler::getInstance().update();

	oldTransform_ = mapTransform_;
	oldState_ = mapState_;

	music.Update();

	for (auto& system : systems_)
	{
		system->update(dt, *this);
	}

	Camera::update(dt);

	deleteDeadEntities();

/*	if (mapState_[player_]->state_ == State::IDLE)
		std::cout << "IDLE" << std::endl;
	else if (mapState_[player_]->state_ == State::WALKING)
		std::cout << "WALKING" << std::endl;
	else if (mapState_[player_]->state_ == State::JUMPING)
		std::cout << "JUMPING" << std::endl;
	else if (mapState_[player_]->state_ == State::FALLING)
		std::cout << "FALLING" << std::endl;
	else if (mapState_[player_]->state_ == State::GRAPPLE)
		std::cout << "GRAPPLE" << std::endl;
	else if (mapState_[player_]->state_ == State::ZIPLINE)
		std::cout << "ZIPLINE" << std::endl;
	else if (mapState_[player_]->state_ == State::ATTACKING)
		std::cout << "ATTACKING" << std::endl;
	else if (mapState_[player_]->state_ == State::DYING)
		std::cout << "DYING" << std::endl;
	else if (mapState_[player_]->state_ == State::DEAD)
		std::cout << "DEAD" << std::endl;*/

	if (InputHandler::getInstance().keyPress(ESCAPE_KEY)) {
		pop_ = true;
	}
	if (InputHandler::getInstance().quitRequested()) {
		quit_ = true;
	}
}

void GameState::render()
{	
	//Setting Rendering Systems
	RenderSystem& renderSystem = *(RenderSystem*)systems_[6];
	PlayerRenderSystem& playerRenderSystem = *(PlayerRenderSystem*)systems_[7];
	ParticleEmitterSystem& particleEmitterSystem = *(ParticleEmitterSystem*)systems_[9];



	//Valores supostamente contidos em level_ (aqduiridos do xml)
	int main_layer 	= 2;
	int max_layers	= 5;

	//Rendering Loop
	for (int i = max_layers; i >= 0; i--){

		level_->render(i);
		renderSystem.render(i, *this);
		if (i == main_layer){
			playerRenderSystem.render(*this);
			//particleEmitterSystem.render();
		}
	}

	if (Resources::DEBUG_COLLISION)
		((CollisionSystem*)systems_[5])->render(*this);

	if (Resources::DEBUG_TRIGGERS)
		showTriggers();
}



void GameState::pause()
{

}

void GameState::resume()
{

}


void GameState::createParticleEmitter()
{
	particleEmitter_ = nextId_;
	nextId_++;

	mapTransform_.emplace(particleEmitter_, new TransformComponent(Rect(300, 250, 32, 32)));
	mapEmitter_.emplace(particleEmitter_, new EmitterComponent(0.01));
	mapTimer_.emplace(particleEmitter_, new TimerComponent());
}

void GameState::loadLevel(std::string target){
	pugi::xml_document 	stage_file;
	pugi::xml_parse_result	p_res;

	p_res = stage_file.load_file(target.c_str());
	if (p_res.status){
		std::cout << "Error Reading Level File: " << p_res.description() << std::endl;
		std::cout << "\tLoad result: " << p_res.description() << std::endl;
		std::cout << "\tStatus code: " << p_res.status << std::endl;

		pop_ = true;
	}
	else
	{

		
		if (level_ != nullptr)
			delete level_;
		level_ = new Level(stage_file.child("world_info"));

		setTriggers(stage_file.child("world_info").child("triggers"));
		setObjects(stage_file.child("world_objects"));

		

		music.Load(stage_file.child("world_info").child("music"));
		music.Play();
	}
}

void GameState::setTriggers(pugi::xml_node objects)
{

	std::string string_music 		= "music";
	std::string string_checkpoint 	= "checkpoint";

	for (auto obj : objects.children())
	{
		if (obj.name() == string_checkpoint){
			checkpoints.emplace_back(TransformComponent(
				Rect(	obj.attribute("x").as_float(),
						obj.attribute("y").as_float(),
						obj.attribute("w").as_float(),
						obj.attribute("h").as_float() ))
				);

		}

		if (obj.name() == string_music){
			musicTriggers.emplace_back(
				std::pair<TransformComponent, std::string>
					(TransformComponent(Rect(
					obj.attribute("x").as_float(),
					obj.attribute("y").as_float(),
					obj.attribute("w").as_float(),
					obj.attribute("h").as_float() )),

					obj.attribute("state").as_string()));
		}

		/*
		if (obj.name() == string_music){
			musicTriggers.emplace_back(
				std::pair<TransformComponent, short int>
					(TransformComponent(Rect(
					obj.attribute("x").as_float(),
					obj.attribute("y").as_float(),
					obj.attribute("w").as_float(),
					obj.attribute("h").as_float() )),

					obj.attribute("state").as_int()));
		}
		*/
	}


	//Failsafe Checking:
	if (checkpoints.empty())
		checkpoints.emplace_back(TransformComponent(Rect(352, 100, 48, 96)));

}

void GameState::setObjects(pugi::xml_node objects)
{

	short int main_layer = 2;

	for (auto obj : objects.children())
	{
		pugi::xml_node aux;

		// TRANSFORM
		aux = obj.child("transform");
		mapTransform_.emplace(nextId_, new TransformComponent(
			Rect( aux.child("rect").attribute("x").as_float(),
			      aux.child("rect").attribute("y").as_float(),
			      aux.child("rect").attribute("w").as_float(),
			      aux.child("rect").attribute("h").as_float() ),
			Vec2( aux.child("scale").attribute("x").as_float(),
			      aux.child("scale").attribute("y").as_float() ),
			aux.child("rotation").attribute("value").as_float()
		));

		// RENDER
		if ((aux = obj.child("render")))
		{
			RenderComponent* renderComp = new RenderComponent();

			for (auto sprite : aux.children())
			{
				State state = (State)sprite.attribute("state").as_int();
				if (!sprite.attribute("loop_back_frame"))
					renderComp->addSprite(state, Sprite(sprite.attribute("filename").value(), 
					                                    sprite.attribute("frame_count").as_int(),
					                                    sprite.attribute("frame_time").as_float()));
				else
					renderComp->addSprite(state, Sprite(sprite.attribute("filename").value(), 
					                                    sprite.attribute("frame_count").as_int(),
					                                    sprite.attribute("frame_time").as_float(),
					                                    sprite.attribute("loop_back_frame").as_int()));
			}

			if (obj.attribute("layer"))
				mapRender_[obj.attribute("layer").as_int()].emplace(nextId_, renderComp);
			else
				mapRender_[main_layer].emplace(nextId_, renderComp);
		}

		// PLAYER RENDER
		if ((aux = obj.child("player_render")))
		{
			for (auto sprite : aux.children())
			{
				State state = (State)sprite.attribute("state").as_int();
				UmbrellaState umb = (UmbrellaState)sprite.attribute("umbrella_state").as_int();
				UmbrellaDirection umbDir = (UmbrellaDirection)sprite.attribute("umbrella_direction").as_int();
				if (!sprite.attribute("loop_back_frame"))
					playerRenderComponent_.addSprite(state, umb, umbDir, Sprite(sprite.attribute("filename").value(), 
					                                                            sprite.attribute("frame_count").as_int(),
					                                                            sprite.attribute("frame_time").as_float()));
				else
					playerRenderComponent_.addSprite(state, umb, umbDir, Sprite(sprite.attribute("filename").value(), 
					                                                            sprite.attribute("frame_count").as_int(),
					                                                            sprite.attribute("frame_time").as_float(),
					                                                            sprite.attribute("loop_back_frame").as_int()));
			}

			player_ = nextId_;
		}

		// SOUND
		if ((aux = obj.child("sound")))
		{
			mapSound_.emplace(nextId_, new SoundComponent());

			for (auto sound : aux.children())
			{
				State state = (State)sound.attribute("state").as_int();
				mapSound_[nextId_]->addSound( state, Sound(sound.attribute("filename").value()) );
			}
		}

		// COLLIDER
		if ((aux = obj.child("collider")))
		{
			mapCollider_.emplace(nextId_, new ColliderComponent(
				Rect( aux.child("hurtbox").attribute("x").as_float(),
				      aux.child("hurtbox").attribute("y").as_float(),
				      aux.child("hurtbox").attribute("w").as_float(),
				      aux.child("hurtbox").attribute("h").as_float() ),
				Rect( aux.child("hitbox").attribute("x").as_float(),
				      aux.child("hitbox").attribute("y").as_float(),
				      aux.child("hitbox").attribute("w").as_float(),
				      aux.child("hitbox").attribute("h").as_float() )
			));
		}

		// SPEED
		if ((aux = obj.child("speed")))
		{
			mapSpeed_.emplace(nextId_, new SpeedComponent());
		}

		// STATE
		if ((aux = obj.child("state")))
		{
			mapState_.emplace(nextId_, new StateComponent());
		}

		// PLAYER_STATE
		if ((aux = obj.child("player_state")))
		{
			mapState_.emplace(nextId_, new PlayerStateComponent());
		}

		// PHYSICS
		if ((aux = obj.child("physics")))
		{
			mapPhysics_.emplace(nextId_, new PhysicsComponent(aux.attribute("gravity_scale").as_float()));
		}

		// EMITTER
		if ((aux = obj.child("emitter")))
		{
			mapEmitter_.emplace(nextId_, new EmitterComponent(aux.attribute("emission_rate").as_float()));
		}

		// TIMER
		if ((aux = obj.child("timer")))
		{
			mapTimer_.emplace(nextId_, new TimerComponent());
		}

		// ZIPLINE
		if ((aux = obj.child("zipline")))
		{
			mapZipline_.emplace(nextId_, new ZiplineComponent(
				Vec2(aux.child("start").attribute("x").as_float(), aux.child("start").attribute("y").as_float()),
				Vec2(aux.child("end").attribute("x").as_float(), aux.child("end").attribute("y").as_float())
			));
		}

		// HEALTH
		if ((aux = obj.child("health")))
		{
			mapHealth_.emplace(nextId_, new HealthComponent(aux.attribute("value").as_float()));
		}

		// WIND
		if ((aux = obj.child("wind")))
		{
			mapWind_.emplace(nextId_, new WindComponent( (Direction)aux.attribute("direction").as_float(),
			                                             aux.attribute("speed").as_float() ));
		}

		// AI
		if ((aux = obj.child("AI"))){
			short int counter = 0;

			//Remover switch: passar para construtor da IA
			switch (aux.attribute("type").as_int()){

				//Externally-Defined AI
				case 0:
					//std::cout << "AI Detected. Type: " << aux.attribute("type").as_int() << std::endl;
					mapAI_.emplace(nextId_, new AIComponent(aux.attribute("type").as_int()));

					//State Emplacement
					for (pugi::xml_node state = aux.first_child(); state; state = state.next_sibling()){
						//printf("Loading State %d (%.3f)\n", counter, state.attribute("cooldown").as_float());
						//Exclusão de valores inválidos (e de IDLE state)
						if (state.attribute("state").as_int() > 0){
							if (state.attribute("cooldown").as_float() >= 0)
									mapAI_[nextId_]->AddState(state.attribute("state").as_int(), state.attribute("cooldown").as_float());
							else	mapAI_[nextId_]->AddState(state.attribute("state").as_int(), 0.0f);
						}

						for (pugi::xml_node trigger_ = state.first_child(); trigger_; trigger_ = trigger_.next_sibling()){
							//printf("\tNow Loading Trigger: %d -> (%d) -> %d\n", counter, trigger_.attribute("verification").as_int(), trigger_.attribute("target_index").as_int());
							mapAI_[nextId_]->AddTrigger(counter, trigger_.attribute("verification").as_int(), trigger_.attribute("target_index").as_int());
						}
						counter++;
					}
					break;

				//Motionless AI
				default:
					break;
			}
		}
		nextId_++;
	}
}


void GameState::deleteDeadEntities()
{
	int max_layers = 5;

	for (auto state = mapState_.begin(); state != mapState_.end(); ++state )
	{
		if (state->second->state_ == State::DEAD)
		{
			int id = state->first;
			if (id == (int)player_)
			{
				// FAZ ALGUMA COISA
				// VOLTA PRO CHECKPOINT
				state->second->state_ = State::IDLE;
				mapTransform_[player_]->rect_.x(400);
				mapTransform_[player_]->rect_.y(400);
				mapHealth_[player_]->health_ = 1;
			}
			else
			{
				mapTransform_.erase(id);
				state = mapState_.erase(state);
				mapPhysics_.erase(id);
				mapCollider_.erase(id);
				mapSpeed_.erase(id);
				mapEmitter_.erase(id);
				mapTimer_.erase(id);
				mapZipline_.erase(id);
				mapSound_.erase(id);
				mapHealth_.erase(id);

				for (int i = 0; i <= max_layers; i++)	//era para ser i < max_layers, segundo o que estava escrito
					mapRender_[i].erase(id);

				--state;
			}
		}
	}
}

//----------------------------------------------------------------------

void GameState::showTriggers(){
	Rect colRect_;
	SDL_Rect drawRect_;

	SDL_Renderer* context = Game::getInstance().getRenderer();
	SDL_SetRenderDrawBlendMode(context, SDL_BLENDMODE_BLEND);

	SDL_SetRenderDrawColor(context, 0, 0, 255, 128);
	for (auto& box : checkpoints){
		
		colRect_ = box.rect_;
		drawRect_.x = (colRect_.x() - Camera::pos_.x());
		drawRect_.y = (colRect_.y() - Camera::pos_.y());
		drawRect_.w = colRect_.w();
		drawRect_.h = colRect_.h();
		SDL_RenderFillRect(context,	&drawRect_);
	}

	SDL_SetRenderDrawColor(context, 255, 0, 0, 128);
	for (auto& box : musicTriggers){
		
		colRect_ = box.first.rect_;
		drawRect_.x = (colRect_.x() - Camera::pos_.x());
		drawRect_.y = (colRect_.y() - Camera::pos_.y());
		drawRect_.w = colRect_.w();
		drawRect_.h = colRect_.h();

		SDL_RenderFillRect(context,	&drawRect_);
	}
}