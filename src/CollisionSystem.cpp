#include "../include/CollisionSystem.hpp"
#include "../include/Resources.hpp"
#include "../include/Camera.hpp"
#include "../include/Sprite.hpp"
#include "../include/Game.hpp"
/*#include "../include/TransformComponent.hpp"
#include "../include/ColliderComponent.hpp"
#include "../include/SpeedComponent.hpp"
#include "../include/StateComponent.hpp"
#include "../include/ZiplineComponent.hpp"
#include "../include/WindComponent.hpp"*/

CollisionSystem::CollisionSystem()
{

}

void CollisionSystem::update(float dt, GameState& gameState)
{
	int player = gameState.player_;
	CollisionMap& collisionMap = gameState.getCollisionMap();
	std::map<int, TransformComponent*> oldTransform = gameState.oldTransform_;
	std::map<int, TransformComponent*> transform = gameState.mapTransform_;
	std::map<int, ColliderComponent*> collider = gameState.mapCollider_;
	std::map<int, SpeedComponent*> speed = gameState.mapSpeed_;
	std::map<int, StateComponent*> oldState = gameState.oldState_;
	std::map<int, StateComponent*> state = gameState.mapState_;
	std::map<int, ZiplineComponent*> zipline = gameState.mapZipline_;
	std::map<int, WindComponent*> wind = gameState.mapWind_;
	std::map<int, HealthComponent*> health = gameState.mapHealth_;

	collidersToRender.clear();

	updateZipline(player, transform, collider, speed, oldState, state, zipline);
	updateWind(dt, player, transform, collider, /*speed, oldState,*/ state, wind);
	updateTerrain(collisionMap, oldTransform, transform, collider, speed, state, health);
	updateCollider(transform, collider, speed, state, health);

	updateTriggers(gameState);

	collidersToRender.emplace_back(collider[player]->hitbox_ + Vec2(transform[player]->rect_.x(), transform[player]->rect_.y()));
}

void CollisionSystem::updateTriggers(GameState& gameState)
{

	TransformComponent& playerTransform = *gameState.mapTransform_[gameState.player_];
	short unsigned int& player_checkpoint = ((PlayerStateComponent*) gameState.mapState_[gameState.player_])->current_checkpoint;
	
	int counter = 0;
	for(auto& triggerbox : gameState.checkpoints){
		if (isColliding(playerTransform.rect_, triggerbox.rect_, 0, 0))
			if (counter > player_checkpoint){
				player_checkpoint = counter;
				std::cout << "Player obtained checkpoint: " << counter << std::endl;
			}
		counter++;
	}

	for(auto& triggerbox : gameState.musicTriggers)
		if (isColliding(playerTransform.rect_, triggerbox.first.rect_, 0, 0)){
			gameState.SetVolumes(triggerbox.second);
		}

	/*
	void updateCollider(
	CollisionMap& collisionMap,
	std::map<int, TransformComponent*> oldTransform,
	std::map<int, TransformComponent*> transform,
	std::map<int, ColliderComponent*> collider,
	std::map<int, SpeedComponent*> speed,
	std::map<int, StateComponent*> state
	*/

}

void CollisionSystem::updateTerrain(
	CollisionMap& collisionMap,
	std::map<int, TransformComponent*> oldTransform,
	std::map<int, TransformComponent*> transform,
	std::map<int, ColliderComponent*> collider,
	std::map<int, SpeedComponent*> speed,
	std::map<int, StateComponent*> state,
	std::map<int, HealthComponent*> health)
{
	// Colisao com o terreno
	for (auto& col : collider)
	{
		Rect finalCollider = col.second->hurtbox_ + transform[col.first]->rect_.getPivot();

		for ( int y = finalCollider.y() / Resources::TILE_HEIGHT;
		      y <= (finalCollider.y() + finalCollider.h()) / Resources::TILE_HEIGHT && y < collisionMap.getHeight();
		      y++ )
		{
			for ( int x = finalCollider.x() / Resources::TILE_WIDTH;
			      x <= (finalCollider.x() + finalCollider.w()) / Resources::TILE_WIDTH && x < collisionMap.getWidth();
			      x++ )
			{
				Rect terrain = Rect( x * Resources::TILE_WIDTH,
				                     y * Resources::TILE_HEIGHT,
				                     Resources::TILE_WIDTH,
				                     Resources::TILE_HEIGHT );

				int collisionType;
				if ((collisionType = collisionMap.at(x,y)) >= 0 && isColliding(finalCollider, terrain, 0, 0))
				{
					switch(collisionType)
					{
						case 0:
							if (state[col.first]->state_ != State::JUMPING)
								correctFloor(transform[col.first]->rect_, col.second->hurtbox_, terrain, speed[col.first]->speed_);
							break;
						case 1:
							correctCeiling(transform[col.first]->rect_, col.second->hurtbox_, terrain, speed[col.first]->speed_);
							break;
						case 2:
							correctWall(transform[col.first]->rect_, col.second->hurtbox_, terrain, speed[col.first]->speed_);
							break;
						case 3:
							correctFloorCeiling(transform[col.first]->rect_, col.second->hurtbox_, terrain, speed[col.first]->speed_);
							break;
						case 4:
							correctAllSides(transform[col.first]->rect_, col.second->hurtbox_, terrain, speed[col.first]->speed_);
							break;
						case 5:
							if (state[col.first]->state_ != State::JUMPING)
								correctDiagonalUp(transform[col.first]->rect_, col.second->hurtbox_, terrain, speed[col.first]->speed_);
							break;
						case 6:
							if (state[col.first]->state_ != State::JUMPING)
								correctDiagonalDown(transform[col.first]->rect_, col.second->hurtbox_, terrain, speed[col.first]->speed_);
							break;
						case 7:
							if (health.find(col.first) != health.end())
								health[col.first]->health_--;
							break;
					}

					if (speed[col.first]->speed_.y() == 0 && state[col.first]->state_ != State::ATTACKING && state[col.first]->state_ != State::DYING)
					{
						state[col.first]->state_ = speed[col.first]->speed_.x() == 0 ? State::IDLE : State::WALKING;
					}

					// Atualizar colisor que foi movido
					finalCollider = col.second->hurtbox_ + transform[col.first]->rect_.getPivot();

					// collidersToRender.emplace_back(terrain);
				}
			}
		}
	}
}

void CollisionSystem::updateCollider(
	std::map<int, TransformComponent*> transform,
	std::map<int, ColliderComponent*> collider,
	std::map<int, SpeedComponent*> speed,
	std::map<int, StateComponent*> state,
	std::map<int, HealthComponent*> health)
{
	// HITBOX COM HURTBOX (ATAQUE E DANO)
	for (auto col = collider.begin(); col != collider.end(); ++col)
	{
		for (auto col2 = collider.begin(); col2 != collider.end(); ++col2)
		{
			if ( col != col2 &&
			     health.find(col2->first) != health.end() &&
			     col->second->hitbox_ != Rect() &&
			     isColliding( col->second->hitbox_ + transform[col->first]->rect_.getPivot(),
			                  col2->second->hurtbox_ + transform[col2->first]->rect_.getPivot(),
			                  transform[col->first]->rotation_,
			                  transform[col2->first]->rotation_))
			{
				health[col2->first]->health_--;
			}
		}
	}

	// HURTBOX COM HURTBOX (POSICAO)
	for (auto col = collider.begin(); col != collider.end(); ++col)
	{
		for (auto col2 = --collider.end(); col2 != col; --col2)
		{
			if (isColliding( col->second->hurtbox_ + transform[col->first]->rect_.getPivot(),
			                 col2->second->hurtbox_ + transform[col2->first]->rect_.getPivot(),
			                 transform[col->first]->rotation_,
			                 transform[col2->first]->rotation_))
			{
				if (speed.find(col->first) != speed.end())
				{
					correctAllSides(transform[col->first]->rect_, col->second->hurtbox_, col2->second->hurtbox_ + transform[col2->first]->rect_.getPivot(), speed[col->first]->speed_);
					if (speed[col->first]->speed_.y() == 0 && 
						state[col->first]->state_ != State::ATTACKING && 
						state[col->first]->state_ != State::DYING)
					{
						state[col->first]->state_ = speed[col->first]->speed_.x() == 0 ? State::IDLE : State::WALKING;
					}
				}
				else if (speed.find(col2->first) != speed.end())
				{
					correctAllSides(transform[col2->first]->rect_, col2->second->hurtbox_, col->second->hurtbox_ + transform[col->first]->rect_.getPivot(), speed[col2->first]->speed_);
					if (speed[col2->first]->speed_.y() == 0 && 
						state[col2->first]->state_ != State::ATTACKING && 
						state[col2->first]->state_ != State::DYING)
					{
						state[col2->first]->state_ = speed[col2->first]->speed_.x() == 0 ? State::IDLE : State::WALKING;
					}
				}	
			}
		}
	}
}


void CollisionSystem::updateZipline(
	int player,
	std::map<int, TransformComponent*> transform,
	std::map<int, ColliderComponent*> collider,
	std::map<int, SpeedComponent*> speed,
	std::map<int, StateComponent*> oldState,
	std::map<int, StateComponent*> state,
	std::map<int, ZiplineComponent*> zipline)
{
	bool isCollidingZip = false;
	for (auto& zip : zipline)
	{
		if ( (state[player]->state_ == State::GRAPPLE || state[player]->state_ == State::ZIPLINE)  && 
		    isColliding( collider[player]->hitbox_ + Vec2(transform[player]->rect_.x(), transform[player]->rect_.y() ),
		                 transform[zip.first]->rect_ * Rect(1, 1, transform[zip.first]->scale_.x(), transform[zip.first]->scale_.y()),
		                 transform[player]->rotation_,
		                 transform[zip.first]->rotation_ ))
		{
			if (state[player]->state_ != State::ZIPLINE)
			{
				state[player]->state_ = State::ZIPLINE;
				speed[player]->speed_ = Vec2( ProjectX(Resources::PLAYER_ZIPLINE_SPEED, transform[zip.first]->rotation_),
				                              ProjectY(Resources::PLAYER_ZIPLINE_SPEED, transform[zip.first]->rotation_) );
			}
			isCollidingZip = true;
			break;
		}
	}
	if (oldState[player]->state_ == State::ZIPLINE && !isCollidingZip)
	{
		state[player]->state_ = State::FALLING;
	}
}


void CollisionSystem::updateWind(
	float dt,
	int player,
	std::map<int, TransformComponent*> transform,
	std::map<int, ColliderComponent*> collider,
	// std::map<int, SpeedComponent*> speed,
	// std::map<int, StateComponent*> oldState,
	std::map<int, StateComponent*> state,
	std::map<int, WindComponent*> wind)
{
	for (auto& w : wind)
	{
		if (isColliding( collider[player]->hitbox_ + Vec2(transform[player]->rect_.x(), transform[player]->rect_.y() ),
		                 transform[w.first]->rect_ * Rect(1, 1, transform[w.first]->scale_.x(), transform[w.first]->scale_.y()),
		                 transform[player]->rotation_,
		                 transform[w.first]->rotation_ ))
		{
			Vec2 speed;
			PlayerStateComponent& playerState = *(PlayerStateComponent*)state[player];
			switch(w.second->direction_)
			{
				case Direction::W_UP :
					if (playerState.umbrellaState_ == UmbrellaState::OPEN && playerState.umbrellaDirection_ == UmbrellaDirection::UP)
						speed = Vec2(0, -w.second->speed_);
					break;
				case Direction::W_DOWN :
					speed = Vec2(0, w.second->speed_);
					break;
				case Direction::W_LEFT :
					if (playerState.umbrellaState_ == UmbrellaState::OPEN)
					{
						if (playerState.umbrellaDirection_ != UmbrellaDirection::FRONT &&
							playerState.umbrellaDirection_ != UmbrellaDirection::BACK)
						{
							speed = Vec2(-w.second->speed_, 0);
						}
						else if ((playerState.facingRight_ && playerState.umbrellaDirection_ != UmbrellaDirection::FRONT) || 
						         (!playerState.facingRight_ && playerState.umbrellaDirection_ != UmbrellaDirection::BACK))
						{
							speed = Vec2(2 * w.second->speed_, 0);
						}
					}
					else
					{
						speed = Vec2(-w.second->speed_, 0);
					}
					break;
				case Direction::W_RIGHT :
					if (playerState.umbrellaState_ == UmbrellaState::OPEN)
					{
						if (playerState.umbrellaDirection_ != UmbrellaDirection::FRONT &&
							playerState.umbrellaDirection_ != UmbrellaDirection::BACK)
						{
							speed = Vec2(w.second->speed_, 0);
						}
						else if ((playerState.facingRight_ && playerState.umbrellaDirection_ != UmbrellaDirection::BACK) || 
						         (!playerState.facingRight_ && playerState.umbrellaDirection_ != UmbrellaDirection::FRONT))
						{
							speed = Vec2(2 * -w.second->speed_, 0);
						}
					}
					else
					{
						speed = Vec2(w.second->speed_, 0);
					}
					break;
			}
			transform[player]->rect_ += speed * dt;
		}
	}
}


bool CollisionSystem::isColliding(const Rect& a, const Rect& b, float angleOfA, float angleOfB)
{
	Vec2 A[] = { Vec2( a.x(), a.y() + a.h() ),
		Vec2( a.x() + a.w(), a.y() + a.h() ),
		Vec2( a.x() + a.w(), a.y() ),
		Vec2( a.x(), a.y() )
	};
	Vec2 B[] = { Vec2( b.x(), b.y() + b.h() ),
		Vec2( b.x() + b.w(), b.y() + b.h() ),
		Vec2( b.x() + b.w(), b.y() ),
		Vec2( b.x(), b.y() )
	};

	for (auto& v : A) {
		// v = Rotate(v - a.getCenter(), angleOfA) + a.getCenter();
		v -= a.getCenter();
		v.rotate(angleOfA);
		v += a.getCenter();
	}

	for (auto& v : B) {
		// v = Rotate(v - b.getCenter(), angleOfB) + b.getCenter();
		v -= b.getCenter();
		v.rotate(angleOfB);
		v += b.getCenter();
	}

	Vec2 axes[] = { Normalize(A[0] - A[1]), Normalize(A[1] - A[2]), Normalize(B[0] - B[1]), Normalize(B[1] - B[2]) };

	for (auto& axis : axes) {
		float P[4];

		for (int i = 0; i < 4; ++i) P[i] = Dot(A[i], axis);

		float minA = *std::min_element(P, P + 4);
		float maxA = *std::max_element(P, P + 4);

		for (int i = 0; i < 4; ++i) P[i] = Dot(B[i], axis);

		float minB = *std::min_element(P, P + 4);
		float maxB = *std::max_element(P, P + 4);

		if (maxA < minB || minA > maxB)
			return false;
	}

	return true;
}

void CollisionSystem::correctFloor(Rect& entityPos, Rect collider, Rect terrain, Vec2& speed)
{
	float angle = LineInclination(entityPos.getCenter(), terrain.getCenter());
	if (angle >= 40 && angle <= 140 && entityPos.y() + collider.h() - collider.y() <= terrain.y() + terrain.h() / 2 )
	{
		entityPos.y( terrain.y() - collider.h() - collider.y() );
		speed.y(0.0);
	}
}

void CollisionSystem::correctWall(Rect& entityPos, Rect collider, Rect terrain, Vec2& speed)
{
	float angle = LineInclination(entityPos.getCenter(), terrain.getCenter());
	if (angle >= -50 && angle < 50)
	{
		entityPos.x( terrain.x() - collider.w() - collider.x() );
	}
	else if (angle > 130 && angle < 230)
	{
		entityPos.x( terrain.x() + terrain.w() - collider.x() );
	}
}

void CollisionSystem::correctCeiling(Rect& entityPos, Rect collider, Rect terrain, Vec2& speed)
{
	float angle = LineInclination(entityPos.getCenter(), terrain.getCenter());
	if ( ( (angle >= 220 && angle <= 320) || (angle >= -140 && angle <= -40) ) && entityPos.y() - collider.y() >= terrain.y() + terrain.h() / 2 )
	{
		entityPos.y( terrain.y() + terrain.h() - collider.y() );
		speed.y(0.0);
	}
}

void CollisionSystem::correctFloorCeiling(Rect& entityPos, Rect collider, Rect terrain, Vec2& speed)
{
	float angle = LineInclination(entityPos.getCenter(), terrain.getCenter());
	if (angle >= 40 && angle <= 140 && entityPos.y() + collider.h() - collider.y() <= terrain.y() + terrain.h() / 2 )
	{
		entityPos.y( terrain.y() - collider.h() - collider.y() );
		speed.y(0.0);
	}
	else if ( ( (angle >= 220 && angle <= 320) || (angle >= -140 && angle <= -40) ) && entityPos.y() - collider.y() >= terrain.y() + terrain.h() / 2 )
	{
		entityPos.y( terrain.y() + terrain.h() - collider.y() );
		speed.y(0.0);
	}
}

void CollisionSystem::correctAllSides(Rect& entityPos, Rect collider, Rect terrain, Vec2& speed)
{
	float angle = LineInclination(entityPos.getCenter(), terrain.getCenter());
	if (angle >= -56 && angle <= 55)
	{
/*		std::cout << "DIREITA" << std::endl;
		std::cout << angle << std::endl;*/
		entityPos.x( terrain.x() - collider.w() - collider.x() );
	}
	else if (angle > 55 && angle <= 130)
	{
/*		std::cout << "EMBAIXO" << std::endl;
		std::cout << angle << std::endl;*/
		entityPos.y( terrain.y() - collider.h() - collider.y() );
		speed.y(0.0);
	}
	else if (angle > 130 && angle <= 230)
	{
/*		std::cout << "ESQUERDA" << std::endl;
		std::cout << angle << std::endl;*/
		entityPos.x( terrain.x() + terrain.w() - collider.x() );
	}
	else
	{
/*		std::cout << "EM CIMA" << std::endl;
		std::cout << angle << std::endl;*/
		entityPos.y( terrain.y() + terrain.h() - collider.y() );
		speed.y(0.0);
	}
}

void CollisionSystem::correctDiagonalUp(Rect& entityPos, Rect collider, Rect terrain, Vec2& speed)
{
	float angle = LineInclination(entityPos.getCenter(), terrain.getCenter());
	if ( angle >= -55 && angle <= 125 )
	{
		if (collider.getCenter().x() + entityPos.x() - collider.x() >= terrain.x() && 
			collider.getCenter().x() + entityPos.x() - collider.x() <= terrain.x() + terrain.w())
		{
			entityPos.y( terrain.y() + terrain.h() - collider.h() - collider.y() - (collider.getCenter().x() + entityPos.x() - collider.x() - terrain.x()) );
			speed.y(0.0);
		}
	}
}


void CollisionSystem::correctDiagonalDown(Rect& entityPos, Rect collider, Rect terrain, Vec2& speed)
{
	float angle = LineInclination(entityPos.getCenter(), terrain.getCenter());
	if ( angle >= 55 && angle <= 235 )
	{
		if (collider.getCenter().x() + entityPos.x() - collider.x() >= terrain.x() && 
			collider.getCenter().x() + entityPos.x() - collider.x() <= terrain.x() + terrain.w())
		{
			entityPos.y( terrain.y() - collider.h() - collider.y() + (collider.getCenter().x() + entityPos.x() - collider.x() - terrain.x()) );
			speed.y(0.0);
		}
	}
}



void CollisionSystem::render(GameState& gameState)
{
	Rect colRect_;
	Rect transRect_;
	SDL_Rect drawRect_;
	SDL_Renderer* context = Game::getInstance().getRenderer();

	SDL_SetRenderDrawBlendMode(context, SDL_BLENDMODE_BLEND);
	for (auto& collider : gameState.mapCollider_){
		//drawing hitbox
		colRect_ = collider.second->hitbox_;
		transRect_ = gameState.mapTransform_[collider.first]->rect_;
		drawRect_.x = (transRect_.x() + colRect_.x() - Camera::pos_.x());
		drawRect_.y = (transRect_.y() + colRect_.y() - Camera::pos_.y());
		drawRect_.w = colRect_.w();
		drawRect_.h = colRect_.h();

		SDL_SetRenderDrawColor(context, 0, 0, 255, 128);
		SDL_RenderFillRect(context,	&drawRect_);

		colRect_ = collider.second->hurtbox_;
		transRect_ = gameState.mapTransform_[collider.first]->rect_;
		drawRect_.x = (transRect_.x() + colRect_.x() - Camera::pos_.x());
		drawRect_.y = (transRect_.y() + colRect_.y() - Camera::pos_.y());
		drawRect_.w = colRect_.w();
		drawRect_.h = colRect_.h();

		SDL_SetRenderDrawColor(context, 255, 0, 0, 128);
		SDL_RenderFillRect(context,	&drawRect_);
	}
	/*
	for (int i = 0; i < (int)collidersToRender.size(); i++)
	{
		Sprite sp = Sprite();
		sp.setClip(collidersToRender[i].x(), collidersToRender[i].y(), collidersToRender[i].w(), collidersToRender[i].h());
		sp.renderSelection(collidersToRender[i].x() - Camera::pos_.x(), collidersToRender[i].y() - Camera::pos_.y());
	}
	*/
}