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

  std::map<int, TransformComponent*> oldTransform = mapTransform_;

  if(timerComponent->time_ > ec->emissionRate_){
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

    int yAux = rand() % 10;
    mapSpeed_.emplace(particle_, new SpeedComponent(Vec2(0, yAux+10)));

    mapCollider_.emplace(particle_, new ColliderComponent(
      Rect(
        mapTransform_[particle_]->rect_.x(),
        mapTransform_[particle_]->rect_.y(),
        16,
        16
      )
    ));

    timerComponent->time_ = 0.0;
  }

  // Cada um desses fors pode ser abstraido futuramente por um sistema
  for(auto& speed : mapSpeed_)
  {
    mapTransform_[speed.first]->rect_ += speed.second->speed_;
  }

  for(auto& collider : mapCollider_)
  {
    collider.second->rect_ = mapTransform_[collider.first]->rect_;
  }

  collisionRainTerrainSystem_.update(
    *this,
    levelCollisionMap,
    oldTransform,
    mapTransform_,
    mapCollider_,
    mapSpeed_
  );

  for(auto t : mapT_)
  {
    t.second.update(dt);
    // std::cout << t.second.get() << std::endl;

    if(t.second.get() > 5) {
      std::cout << "entra" << std::endl;
      mapTransform_.erase(t.first);
      mapRender_.erase(t.first);
      mapT_.erase(t.first);
    }
  }

  for(auto& timer : mapTimer_)
  {
    emissionRateSystem_.update(dt, timer.second);
    if (timer.second->time_  > 20) {
      // Deleta os componentes inuteis
      mapTransform_.erase(timer.first);
      mapRender_.erase(timer.first);
      mapSpeed_.erase(timer.first);
      mapCollider_.erase(timer.first);
      mapTimer_.erase(timer.first); // o iterador do tempo deve ser o ultimo a ser deletado
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
  collisionRainTerrainSystem_.render(mapCollider_);
}

void ParticleEmitterSystem::destroyParticle(int particle)
{
  // Cria o Splat
  int rainSplat = nextId_;
  nextId_++;

  mapTransform_.emplace(rainSplat, new TransformComponent(mapTransform_[particle]->rect_));

  std::unordered_map<std::string, Sprite> rainSplatSprite;
  rainSplatSprite.emplace("IdleState", Sprite("../img/gota.png", 1, 0.1));
  mapRender_.emplace(rainSplat, new RenderComponent(rainSplatSprite));
  mapRender_[rainSplat]->setCurrentSprite("IdleState");

  mapT_.emplace(rainSplat, Timer());

  // Destroy
  mapTransform_.erase(particle);
  mapRender_.erase(particle);
  mapSpeed_.erase(particle);
  mapCollider_.erase(particle);
  mapTimer_.erase(particle);
}
