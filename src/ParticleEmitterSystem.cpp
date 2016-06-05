#include "../include/ParticleEmitterSystem.hpp"

#include <iostream>
#include <time.h>

unsigned int ParticleEmitterSystem::nextId_ = 0;

ParticleEmitterSystem::ParticleEmitterSystem()
{
   srand (time(NULL));
}

void ParticleEmitterSystem::update(
  float dt,
  CollisionMap levelCollisionMap,
  TransformComponent* tc,
  EmitterComponent* ec,
  TimerComponent* timerComponent
)
{
  emissionRateSystem_.update(dt, timerComponent);

  if(timerComponent->time_ > 0.1){
    int particle_ = nextId_;
    nextId_++;

    int xRand = rand() % 1024;
    mapTransform_.emplace(particle_, new TransformComponent(Rect(xRand, 100, 16, 16)));

    // Exemplo soh pra testar, nao esquecer de mudar depois
    std::unordered_map<std::string, Sprite> particleSprite;
  	particleSprite.emplace("IdleState", Sprite("../img/gota.png", 1, 0.1));
    mapRender_.emplace(particle_, new RenderComponent(particleSprite));
    mapRender_[particle_]->setCurrentSprite("IdleState");

    mapTimer_.emplace(particle_, new TimerComponent());

    int yAux = rand() % 5;
    mapSpeed_.emplace(particle_, new SpeedComponent(Vec2(0, yAux+1)));

    mapCollider_.emplace(particle_, new ColliderComponent(
      Rect(
        mapTransform_[particle_]->rect_.x(),
        mapTransform_[particle_]->rect_.y(),
        16,
        16
      )
    ));

    std::map<int, TransformComponent*> oldTransform = mapTransform_;

    // collisionSystem_.update(
    //   levelCollisionMap,
  	// 	oldTransform,
  	// 	mapTransform_,
  	// 	mapCollider_,
  	// 	mapSpeed_
    // );

    timerComponent->time_ = 0.0;
  }

  // Cada um desses fors pode ser abstraido futuramente por um sistema
  for(auto& transform : mapTransform_)
  {
    transform.second->rect_ += mapSpeed_[transform.first]->speed_;
  }

  for(auto& collider : mapCollider_)
  {
    collider.second->rect_ = mapTransform_[collider.first]->rect_;
  }

  for(auto& timer : mapTimer_)
  {
    emissionRateSystem_.update(dt, timer.second);
    if (timer.second->time_  > 8) {
      std::map<int, TransformComponent*>::iterator itTransform = mapTransform_.find (timer.first);
      std::map<int, RenderComponent*>::iterator itRender = mapRender_.find (timer.first);
      std::map<int, TimerComponent*>::iterator itTimer = mapTimer_.find (timer.first);
      std::map<int, SpeedComponent*>::iterator itSpeed = mapSpeed_.find (timer.first);
      std::map<int, ColliderComponent*>::iterator itCollider = mapCollider_.find(timer.first);
      mapTransform_.erase(itTransform);
      mapRender_.erase(itRender);
      mapSpeed_.erase(itSpeed);
      mapCollider_.erase(itCollider);
      mapTimer_.erase(itTimer); // o iterador do tempo deve ser o ultimo a ser deletado
    }
  }
}

void ParticleEmitterSystem::render()
{
  for(auto& render : mapRender_)
  {
    Rect transform = mapTransform_[render.first]->rect_;
    render.second->getCurrentSprite()->render(
      transform.x(),
      transform.y(),
      0,
      0
    );
  }
}
