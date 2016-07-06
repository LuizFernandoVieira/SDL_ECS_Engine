#include "../include/CollisionRainTerrainSystem.hpp"
#include "../include/Resources.hpp"

#include "../include/Camera.hpp"
#include "../include/Sprite.hpp"

#include <iostream>
#include <algorithm>


CollisionRainTerrainSystem::CollisionRainTerrainSystem()
{

}

void CollisionRainTerrainSystem::update(
  ParticleEmitterSystem& particleEmitterSystem,
	CollisionMap& collisionMap,
	std::map<int, TransformComponent*> oldTransfComp,
	std::map<int, TransformComponent*> transfComp,
	std::map<int, ColliderComponent*> colComp,
	std::map<int, SpeedComponent*> speedComp)
{
	// coisaFeia.clear();

  std::vector<int> toDelete;
  std::vector<int> toDeleteNow;

	// Colisao com o terreno
	for (auto& col : colComp)
	{
    Rect collider = col.second->hurtbox_;

		for (int y = collider.y() / Resources::TILE_HEIGHT/* - 1*/;
			y <= (collider.y() + collider.h()) / Resources::TILE_HEIGHT/* + 1*/;
			y++)
		{
			for (int x = collider.x() / Resources::TILE_WIDTH/* - 1*/;
				x <= (collider.x() + collider.w()) / Resources::TILE_WIDTH/* + 1*/;
				x++)
			{
				Rect terrain = Rect(
					x * Resources::TILE_WIDTH,
					y * Resources::TILE_HEIGHT,
					Resources::TILE_WIDTH,
					Resources::TILE_HEIGHT
				);

				if ( (collisionMap.at(x,y) == 0 || collisionMap.at(x,y) == 3 || collisionMap.at(x,y) == 4) &&
              isColliding(collider, terrain, 0, 0))
				{
          if(std::find(toDelete.begin(), toDelete.end(), col.first) == toDelete.end())
          {
            toDelete.emplace_back(col.first);
          }
					// coisaFeia.emplace_back(terrain);
				}
        else if ( collisionMap.at(x,y) == 5 || collisionMap.at(x,y) == 6 &&
              isColliding(collider, terrain, 0, 0))
        {
          toDeleteNow.emplace_back(col.first);
        }

			}
		}
	}

  for(auto d : toDelete)
  {
    particleEmitterSystem.destroyParticle(d);
  }

  for(auto d : toDeleteNow)
  {
    particleEmitterSystem.destroyParticleNow(d);
  }
}


bool CollisionRainTerrainSystem::isColliding(const Rect& a, const Rect& b, float angleOfA, float angleOfB)
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

void CollisionRainTerrainSystem::render(std::map<int, ColliderComponent*> collidersForRendering)
{
  for(auto col : collidersForRendering)
  {
    Sprite sp = Sprite();
    sp.setClip(col.second->hurtbox_.x(), col.second->hurtbox_.y(), col.second->hurtbox_.w(), col.second->hurtbox_.h());
    sp.renderSelection(col.second->hurtbox_.x() - Camera::pos_.x(), col.second->hurtbox_.y() - Camera::pos_.y());
  }

	// for (int i = 0; i < (int)coisaFeia.size(); i++)
	// {
	// 	Sprite sp = Sprite();
	// 	sp.setClip(coisaFeia[i].x(), coisaFeia[i].y(), coisaFeia[i].w(), coisaFeia[i].h());
	// 	sp.renderSelection(coisaFeia[i].x() - Camera::pos_.x(), coisaFeia[i].y() - Camera::pos_.y());
	// }
}
