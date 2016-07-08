#include "../include/ParticleEmitterSystem.hpp"
#include "../include/StateComponent.hpp"
#include "../include/Camera.hpp"

#include <iostream>
#include <time.h>

unsigned int ParticleEmitterSystem::nextId_ = 0;
std::map<int, RenderComponent*> ParticleEmitterSystem::mapR_;
std::map<int, TransformComponent*> ParticleEmitterSystem::mapTransform_;

ParticleEmitterSystem::ParticleEmitterSystem()
{
	srand (time(NULL));
	mapR_.clear();
}

ParticleEmitterSystem::~ParticleEmitterSystem()
{
	nextId_ = 0;
	mapTransform_.clear();
	mapR_.clear();
	mapTimer_.clear();
	mapSpeed_.clear();
	mapCollider_.clear();
	mapT_.clear();
}

void ParticleEmitterSystem::destroyAll()
{
	nextId_ = 0;
	mapTransform_.clear();
	mapR_.clear();
	mapTimer_.clear();
	mapSpeed_.clear();
	mapCollider_.clear();
	mapT_.clear();
}

void ParticleEmitterSystem::update(float dt, GameState& gameState)
{
	CollisionMap& levelCollisionMap = gameState.getCollisionMap();
	// TransformComponent* tc = gameState.mapTransform_[gameState.particleEmitter_];

	EmitterComponent* ec = gameState.mapEmitter_[gameState.particleEmitter_];
	if (ec == NULL) return;
	TimerComponent* timerComponent = gameState.mapTimer_[gameState.particleEmitter_];

	emissionRateSystem_.update(dt, timerComponent);

	std::map<int, TransformComponent*> oldTransform = mapTransform_;

	if(timerComponent->time_ > ec->emissionRate_){
		for(int i=0; i<6; i++)
		{
			int particle_ = nextId_;
			nextId_++;

			int xRand = rand() % (ec->xWidth_*2);
			mapTransform_.emplace(particle_, new TransformComponent(Rect(Camera::pos_.x() + xRand - 512, 0, 16, 16)));

			// Exemplo soh pra testar, nao esquecer de mudar depois
			std::unordered_map<State, Sprite> particleSprite;
			particleSprite.emplace(State::IDLE, Sprite(ec->particlePath_.c_str(), 1, 0.1));
			mapR_.emplace(particle_, new RenderComponent(particleSprite));

			mapTimer_.emplace(particle_, new TimerComponent());

			int yAux = rand() % 10;
			mapSpeed_.emplace(particle_, new SpeedComponent(Vec2(0, yAux+ec->ySpeed_)));

			mapCollider_.emplace(particle_, new ColliderComponent(
				Rect(
					mapTransform_[particle_]->rect_.x(),
					mapTransform_[particle_]->rect_.y(),
					16,
					16
				)
			));
		}

		timerComponent->time_ = 0.0;
	}

	// Cada um desses fors pode ser abstraido futuramente por um sistema
	for(auto& speed : mapSpeed_)
	{
		mapTransform_[speed.first]->rect_ += speed.second->speed_;
	}

	for(auto& collider : mapCollider_)
	{
		collider.second->hurtbox_ = mapTransform_[collider.first]->rect_;
	}

	collisionRainTerrainSystem_.update(
		*this,
		levelCollisionMap,
		oldTransform,
		mapTransform_,
		mapCollider_,
		mapSpeed_
	);

	for(auto& render : mapR_)
	{
		render.second->getSprite(State::IDLE).update(dt);
	}

	for(auto t : mapT_)
	{
		t.second->update(dt);

		if(t.second->get() > 2) {
			mapTransform_.erase(t.first);
			mapR_.erase(t.first);
			mapT_.erase(t.first);
		}
	}

	for(auto& timer : mapTimer_)
	{
		emissionRateSystem_.update(dt, timer.second);
		if (timer.second->time_  > 20) {
			// Deleta os componentes inuteis
			mapTransform_.erase(timer.first);
			mapR_.erase(timer.first);
			mapSpeed_.erase(timer.first);
			mapCollider_.erase(timer.first);
			mapTimer_.erase(timer.first); // o iterador do tempo deve ser o ultimo a ser deletado
		}
	}
}

void ParticleEmitterSystem::render()
{
	for(auto& render : mapR_)
	{
		Rect transform = mapTransform_[render.first]->rect_;
		render.second->getSprite(State::IDLE).render(
			transform.x(),
			transform.y(),
			0,
			0
		);
	}
	// collisionRainTerrainSystem_.render(mapCollider_);
}

void ParticleEmitterSystem::destroyParticleNow(int particle)
{
	mapTransform_.erase(particle);
	mapR_.erase(particle);
	mapSpeed_.erase(particle);
	mapCollider_.erase(particle);
	mapTimer_.erase(particle);
}

void ParticleEmitterSystem::destroyParticle(int particle)
{
	// Cria o Splat
	int rainSplat = nextId_;
	nextId_++;

	mapTransform_.emplace(rainSplat, new TransformComponent(mapTransform_[particle]->rect_));

	std::unordered_map<State, Sprite> rainSplatSprite;
	rainSplatSprite.emplace(State::IDLE, Sprite("../img/waterdrop-colision.png", 3, 0.1));
	mapR_.emplace(rainSplat, new RenderComponent(rainSplatSprite));

	mapT_.emplace(rainSplat, new Timer());

	// Destroy
	mapTransform_.erase(particle);
	mapR_.erase(particle);
	mapSpeed_.erase(particle);
	mapCollider_.erase(particle);
	mapTimer_.erase(particle);
}
