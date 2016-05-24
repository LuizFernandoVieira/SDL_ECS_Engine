#include "../include/CollisionSystem.hpp"
#include "../include/Globals.hpp"

#include "../include/Camera.hpp"
#include "../include/Sprite.hpp"
#include <iostream>

CollisionSystem::CollisionSystem()
{

}

void CollisionSystem::update(
	CollisionMap& collisionMap,
	std::map<int, TransformComponent*> oldTransfComp,
	std::map<int, TransformComponent*> transfComp,
	std::map<int, ColliderComponent*> colComp,
	std::map<int, SpeedComponent*> speedComp)
{
	// coisaFeia.clear();
	
	// Colisao com o terreno
	for (auto& col : colComp)
	{
		Rect collider = col.second->rect_ + Vec2(transfComp[col.first]->rect_.x(), transfComp[col.first]->rect_.y() );
		
		for (int y = collider.y() / Globals::TILE_HEIGHT/* - 1*/;
			y <= (collider.y() + collider.h()) / Globals::TILE_HEIGHT/* + 1*/;
			y++)
		{
			for (int x = collider.x() / Globals::TILE_WIDTH/* - 1*/;
				x <= (collider.x() + collider.w()) / Globals::TILE_WIDTH/* + 1*/;
				x++)
			{
				Rect terrain = Rect(
					x * Globals::TILE_WIDTH, 
					y * Globals::TILE_HEIGHT, 
					Globals::TILE_WIDTH, 
					Globals::TILE_HEIGHT
				);

				if (collisionMap.at(x,y) == 0 && isColliding(collider, terrain, 0, 0))
				{
					correctPosition(transfComp[col.first]->rect_, oldTransfComp[col.first]->rect_, terrain, speedComp[col.first]->speed_);
					// coisaFeia.emplace_back(terrain);
				}
			}
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


void CollisionSystem::correctPosition(Rect& entityPos, Rect oldPos, Rect terrain, Vec2& speed)
{
	float angle = LineInclination(oldPos.getCenter(), terrain.getCenter());
	if (angle >= -45 && angle < 45) // entity colidiu à direita
	{
		// std::cout << "COLIDIU A DIREITA" << std::endl;
		entityPos.x( terrain.x() - entityPos.w() );
	}
	else if (angle >= 45 && angle <= 135) // entity estava acima do colisor
	{
		// std::cout << "COLIDIU EMBAIXO" << std::endl;
		entityPos.y( terrain.y() - entityPos.h() );
		speed.y(0.0);
	}
	else if (angle > 135 && angle < 225) // entity colidiu à esquerda
	{
		// std::cout << "COLIDIU A ESQUERDA" << std::endl;
		entityPos.x( terrain.x() + terrain.w() );
	}
	else // entity estava abaixo do colisor
	{
		// std::cout << "COLIDIU EM CIMA" << std::endl;
		entityPos.y( terrain.y() + terrain.h() );
		speed.y(0.0);
	}
}

/*void CollisionSystem::render()
{
	for (int i = 0; i < (int)coisaFeia.size(); i++)
	{
		Sprite sp = Sprite();
		sp.setClip(coisaFeia[i].x(), coisaFeia[i].y(), coisaFeia[i].w(), coisaFeia[i].h());
		sp.renderSelection(coisaFeia[i].x() - Camera::pos_.x(), coisaFeia[i].y() - Camera::pos_.y());
	}
}*/