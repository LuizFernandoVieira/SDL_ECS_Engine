#include "../include/CollisionSystem.hpp"
#include "../include/Resources.hpp"

#include "../include/Camera.hpp"
#include "../include/Sprite.hpp"

CollisionSystem::CollisionSystem()
{

}

void CollisionSystem::update(
	int player,
	CollisionMap& collisionMap,
	std::map<int, TransformComponent*> oldTransform,
	std::map<int, TransformComponent*> transform,
	std::map<int, ColliderComponent*> collider,
	std::map<int, SpeedComponent*> speed,
	std::map<int, StateComponent*> oldState,
	std::map<int, StateComponent*> state,
	std::map<int, ZiplineComponent*> zipline)
{
	collidersToRender.clear();

	updateTerrain(collisionMap, oldTransform, transform, collider, speed, state);
	updateCollider(collisionMap, oldTransform, transform, collider, speed, state);
	updateZipline(player, collisionMap, transform, collider, speed, oldState, state, zipline);

	collidersToRender.emplace_back(collider[player]->hitbox_ + Vec2(transform[player]->rect_.x(), transform[player]->rect_.y()));
}


void CollisionSystem::updateTerrain(
	CollisionMap& collisionMap,
	std::map<int, TransformComponent*> oldTransform,
	std::map<int, TransformComponent*> transform,
	std::map<int, ColliderComponent*> collider,
	std::map<int, SpeedComponent*> speed,
	std::map<int, StateComponent*> state)
{
	// Colisao com o terreno
	for (auto& col : collider)
	{
		Rect finalCollider = col.second->hurtbox_ + Vec2(transform[col.first]->rect_.x(), transform[col.first]->rect_.y() );

		for (int y = finalCollider.y() / Resources::TILE_HEIGHT/* - 1*/;
			y <= (finalCollider.y() + finalCollider.h()) / Resources::TILE_HEIGHT && y < collisionMap.getHeight()/* + 1*/;
			y++)
		{
			for (int x = finalCollider.x() / Resources::TILE_WIDTH/* - 1*/;
				x <= (finalCollider.x() + finalCollider.w()) / Resources::TILE_WIDTH && x < collisionMap.getWidth()/* + 1*/;
				x++)
			{
				Rect terrain = Rect(
					x * Resources::TILE_WIDTH,
					y * Resources::TILE_HEIGHT,
					Resources::TILE_WIDTH,
					Resources::TILE_HEIGHT
				);

				int collisionType;
				if ((collisionType = collisionMap.at(x,y)) >= 0 && isColliding(finalCollider, terrain, 0, 0))
				{
					if (collisionType == 0)
					{
						correctPosSolid(transform[col.first]->rect_, oldTransform[col.first]->rect_, terrain, speed[col.first]->speed_, state[col.first]);
					}
					else if (collisionType == 1)
					{
						correctPosDiagonalUp(transform[col.first]->rect_, oldTransform[col.first]->rect_, terrain, speed[col.first]->speed_, state[col.first]);
					}
					else if (collisionType == 2)
					{
						correctPosDiagonalDown(transform[col.first]->rect_, oldTransform[col.first]->rect_, terrain, speed[col.first]->speed_, state[col.first]);
					}
					else if (collisionType == 3)
					{
						correctPosCorner(transform[col.first]->rect_, oldTransform[col.first]->rect_, terrain, speed[col.first]->speed_, state[col.first]);
					}

					// Atualizar colisor que foi movido
					finalCollider = col.second->hurtbox_ + Vec2(transform[col.first]->rect_.x(), transform[col.first]->rect_.y() );

					// collidersToRender.emplace_back(terrain);
				}
			}
		}
	}
}

void CollisionSystem::updateCollider(
	CollisionMap& collisionMap,
	std::map<int, TransformComponent*> oldTransform,
	std::map<int, TransformComponent*> transform,
	std::map<int, ColliderComponent*> collider,
	std::map<int, SpeedComponent*> speed,
	std::map<int, StateComponent*> state)
{
/*	for (auto col = collider.begin(); col != collider.end(); ++col)
	{
		for (auto col2 = col + 1; col2 != collider.end(); ++col2)
		{
			if (isColliding( col.second->hurtbox_ + Vec2(transform[col.first]->rect_.x(), transform[col.first]->rect_.y()),
			                 col2.second->hurtbox_ + Vec2(transform[col2.first]->rect_.x(), transform[col2.first]->rect_.y()),
			                 transform[col.first]->rotation_,
			                 transform[col2.first]->rotation_))
			{
				if (speed.find(col.first) != speed.end())
				{
					correctPosSolid(transform[col.first], oldTransform[col.first], transform[col2.first], speed[col.first]->speed_, state[col.first]);
				}
				else if (speed.find(col2.first) != speed.end())
				{
					correctPosSolid(transform[col2.first], oldTransform[col2.first], transform[col.first], speed[col2.first]->speed_, state[col2.first]);
				}
			}
		}
	}*/
}


void CollisionSystem::updateZipline(
	int player,
	CollisionMap& collisionMap,
	std::map<int, TransformComponent*> transform,
	std::map<int, ColliderComponent*> collider,
	std::map<int, SpeedComponent*> speed,
	std::map<int, StateComponent*> oldState,
	std::map<int, StateComponent*> state,
	std::map<int, ZiplineComponent*> zipline)
{
	for (auto& zip : zipline)
	{
		if ( (state[player]->state_ == State::GRAPPLE || state[player]->state_ == State::ZIPLINE)  && 
		    isColliding( collider[player]->hitbox_ + Vec2(transform[player]->rect_.x(), transform[player]->rect_.y() ),
		                 transform[zip.first]->rect_ * Rect(1, 1, transform[zip.first]->scale_.x(), transform[zip.first]->scale_.y()),
		                 transform[player]->rotation_,
		                 transform[zip.first]->rotation_ ))
		{
			state[player]->state_ = State::ZIPLINE;
			speed[player]->speed_ = Vec2( ProjectX(Resources::PLAYER_ZIPLINE_SPEED, transform[zip.first]->rotation_),
			                              ProjectY(Resources::PLAYER_ZIPLINE_SPEED, transform[zip.first]->rotation_) );
		}
		else if (oldState[player]->state_ == State::ZIPLINE)
		{
			state[player]->state_ = State::FALLING;
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


void CollisionSystem::correctPosSolid(Rect& entityPos, Rect oldPos, Rect terrain, Vec2& speed, StateComponent* state)
{
	float angle = LineInclination(oldPos.getCenter(), terrain.getCenter());
	if (angle >= -55 && angle < 55) // entity colidiu à direita
	{
		// std::cout << "COLIDIU A DIREITA" << std::endl;
		entityPos.x( terrain.x() - entityPos.w() );
	}
	else if (angle >= 55 && angle <= 130) // entity estava acima do colisor
	{
		// std::cout << "COLIDIU EMBAIXO" << std::endl;
		entityPos.y( terrain.y() - entityPos.h() );
		speed.y(0.0);
		if (state->state_ != State::ATTACKING)
			state->state_ = speed.x() == 0 ? State::IDLE : State::WALKING;
	}
	else if (angle > 130 && angle < 235) // entity colidiu à esquerda
	{
		// std::cout << "COLIDIU A ESQUERDA" << std::endl;
		entityPos.x( terrain.x() + terrain.w() );
	}
	else // entity estava abaixo do colisor
	{
		// std::cout << "COLIDIU EM CIMA" << std::endl;
		if (state->state_ != JUMPING)
		{
			entityPos.y( terrain.y() + terrain.h() );
			speed.y(0.0);
			state->state_ = State::FALLING;
		}
	}
}


void CollisionSystem::correctPosDiagonalUp(Rect& entityPos, Rect oldPos, Rect terrain, Vec2& speed, StateComponent* state)
{
	float angle = LineInclination(oldPos.getCenter(), terrain.getCenter());
	if (angle >= -55 && angle < 55) // entity colidiu à direita
	{
		if (entityPos.getCenter().x() >= terrain.x() && 
			entityPos.getCenter().x() <= terrain.x() + terrain.w() && 
			state->state_ != JUMPING)
		{
			// std::cout << "COLIDIU A DIREITA" << std::endl;
			entityPos.y( terrain.y() + terrain.h() - entityPos.h() - (entityPos.getCenter().x() - terrain.x()) );
			speed.y(0.0);
			state->state_ = speed.x() == 0 ? State::IDLE : State::WALKING;
		}
	}
	else if (angle >= 55 && angle <= 125 && state->state_ != JUMPING) // entity estava acima do colisor
	{
		if (entityPos.getCenter().x() >= terrain.x() && 
			entityPos.getCenter().x() <= terrain.x() + terrain.w() && 
			state->state_ != JUMPING)
		{
			// std::cout << "COLIDIU EMBAIXO" << std::endl;
			entityPos.y( terrain.y() + terrain.h() - entityPos.h() - (entityPos.getCenter().x() - terrain.x()) );
			speed.y(0.0);
			if (state->state_ != State::ATTACKING)
				state->state_ = speed.x() == 0 ? State::IDLE : State::WALKING;
		}
	}
	else if (angle > 125 && angle < 235) // entity colidiu à esquerda
	{
		// std::cout << "COLIDIU A ESQUERDA" << std::endl;
		entityPos.x( terrain.x() + terrain.w() );
	}
/*	else // entity estava abaixo do colisor
	{
		std::cout << "COLIDIU EM CIMA" << std::endl;
		entityPos.y( terrain.y() + terrain.h() );
		speed.y(0.0);
		state->state_ = State::FALLING;
	}*/
}


void CollisionSystem::correctPosDiagonalDown(Rect& entityPos, Rect oldPos, Rect terrain, Vec2& speed, StateComponent* state)
{
	float angle = LineInclination(oldPos.getCenter(), terrain.getCenter());
	if (angle >= -55 && angle < 55) // entity colidiu à direita
	{
		entityPos.x( terrain.x() - entityPos.w() );
	}
	else if (angle >= 55 && angle <= 125 && state->state_ != JUMPING) // entity estava acima do colisor
	{
		if (entityPos.getCenter().x() >= terrain.x() && 
			entityPos.getCenter().x() <= terrain.x() + terrain.w() && 
			state->state_ != JUMPING)
		{
			// std::cout << "COLIDIU EMBAIXO" << std::endl;
			entityPos.y( terrain.y() /*+ terrain.h()*/ - entityPos.h() + (entityPos.getCenter().x() - terrain.x()) );
			speed.y(0.0);
			state->state_ = speed.x() == 0 ? State::IDLE : State::WALKING;
		}
	}
	else if (angle > 125 && angle < 235) // entity colidiu à esquerda
	{
		// std::cout << "COLIDIU A ESQUERDA" << std::endl;
		// entityPos.x( terrain.x() + terrain.w() );
		if (entityPos.getCenter().x() >= terrain.x() && 
			entityPos.getCenter().x() <= terrain.x() + terrain.w() && 
			state->state_ != JUMPING)
		{
			// std::cout << "COLIDIU EMBAIXO" << std::endl;
			entityPos.y( terrain.y() /*+ terrain.h()*/ - entityPos.h() + (entityPos.getCenter().x() - terrain.x()) );
			speed.y(0.0);
			if (state->state_ != State::ATTACKING)
				state->state_ = speed.x() == 0 ? State::IDLE : State::WALKING;
		}
	}
/*	else // entity estava abaixo do colisor
	{
		std::cout << "COLIDIU EM CIMA" << std::endl;
		entityPos.y( terrain.y() + terrain.h() );
		speed.y(0.0);
		state->state_ = State::FALLING;
	}*/
}


void CollisionSystem::correctPosCorner(Rect& entityPos, Rect oldPos, Rect terrain, Vec2& speed, StateComponent* state)
{
	float angle = LineInclination(oldPos.getCenter(), terrain.getCenter());
	if (angle >= -55 && angle < 55) // entity colidiu à direita
	{
		// std::cout << "COLIDIU A DIREITA" << std::endl;
		// entityPos.x( terrain.x() - entityPos.w() );
	}
	else if (angle >= 55 && angle <= 125) // entity estava acima do colisor
	{
		// std::cout << "COLIDIU EMBAIXO" << std::endl;
		entityPos.y( terrain.y() - entityPos.h() );
		speed.y(0.0);
		if (state->state_ != State::ATTACKING)
			state->state_ = speed.x() == 0 ? State::IDLE : State::WALKING;
	}
	else if (angle > 125 && angle < 235) // entity colidiu à esquerda
	{
		// std::cout << "COLIDIU A ESQUERDA" << std::endl;
		// entityPos.x( terrain.x() + terrain.w() );
	}
	else // entity estava abaixo do colisor
	{
		// std::cout << "COLIDIU EM CIMA" << std::endl;
		entityPos.y( terrain.y() + terrain.h() );
		speed.y(0.0);
		state->state_ = State::FALLING;
	}
}



void CollisionSystem::render()
{
	for (int i = 0; i < (int)collidersToRender.size(); i++)
	{
		Sprite sp = Sprite();
		sp.setClip(collidersToRender[i].x(), collidersToRender[i].y(), collidersToRender[i].w(), collidersToRender[i].h());
		sp.renderSelection(collidersToRender[i].x() - Camera::pos_.x(), collidersToRender[i].y() - Camera::pos_.y());
	}
}