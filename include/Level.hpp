#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>

#include "TransformComponent.hpp"
#include "CollisionMap.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"
#include "CollisionMap.hpp"
#include "TransformComponent.hpp"
#include "StaticSprite.hpp"
#include "pugixml.hpp"

class Level
{
public:
	Level();
	Level(pugi::xml_node source);
	~Level();
	void render(int layer);
	// std::vector<std::pair<int, TransformComponent*>> createTerrain(unsigned int&);
	CollisionMap& getCollisionMap();

private:
	//StaticSprite bg;
	TileSet tileSet_;
	TileMap tileMap_;
	CollisionMap collisionMap_;

	//std::vector<StaticSprite> screen;
	std::vector<StaticSprite> screen;
};


/*
			Class ScreenLayer{
				//Sprite e Tilemap Herdam de Screenlayer (!!!!)
					- CHEAT CODE TOTAL

				virtual ScreenLayer() = 0;
				virtual ScreenLayer(std::string source) = 0;
				virtual void Render() = 0;
			};

			class Level{
				private: 
					std::vector<ScreenLayer> screen;
			}

			Level::ReadLayers(pugi::xml_node source){
				for (auto pugi::xml_node layer_node : source.child("layer")){
					if (layer_node.attribute("type").value() == "tile")
						tile = true;
					else tile = false;

					screen.emplace(ScreenLayer()) ;

					// ---------------
					switch (tile){
						case true:

						case false:

						default:
						return;
					}
					// ---------------
				}
			}

*/


#endif