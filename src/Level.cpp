#include "../include/Level.hpp"
#include "../include/Resources.hpp"
#include "../include/pugixml.hpp"

#include "../include/ScreenImageLayer.hpp"

#include "../include/game.hpp"
Level::Level() :
	tileSet_(Resources::TILE_WIDTH, Resources::TILE_HEIGHT, Resources::TILE_SET_IMG.c_str()),
	tileMap_(Resources::TILE_MAP_TXT.c_str(), &tileSet_),
	collisionMap_(Resources::COLLISION_MAP_TXT.c_str())
{
	screen.emplace_back(new ImageLayer("../img/loading.png"));	//failsafe

	max_layers = 0;
	main_layer = 0;
}

Level::Level(pugi::xml_node source) :
	tileSet_(Resources::TILE_WIDTH, Resources::TILE_HEIGHT,
					source.child("tileset").attribute("file").value()),
	tileMap_(		source.child("tilemap").attribute("file").value(), &tileSet_),
	collisionMap_(	source.child("collision_map").attribute("file").value())
{
	short int current_layer = 0;
	short int c_tiled_layer = 0;

	max_layers = 0;
	main_layer = 0;

	for (pugi::xml_node layer = source.child("layers").first_child(); layer ; layer = layer.next_sibling()){
		
		if (!layer.attribute("tiled").as_bool())
			/*
				Quando implementação de tiles for feita
			if (layer.attribute("tiled").as_bool())
					screen.emplace_back(new TiledLayer(layer.attribute("file").value(), &tileSet_));
			else 	screen.emplace_back(new ImageLayer(layer.attribute("file").value()));
			*/

			screen.emplace_back(new ImageLayer(layer.attribute("file").value()));
			//screen.emplace_back(new ImageLayer());


			if(layer.attribute("parallax_x") && layer.attribute("parallax_y"))
				screen[current_layer]->SetParallax(
					layer.attribute("parallax_x").as_float(),
					layer.attribute("parallax_y").as_float());

			if(layer.attribute("scale_x") && layer.attribute("scale_y"))
				screen[current_layer]->SetScale(
					layer.attribute("scale_x").as_float(),
					layer.attribute("scale_y").as_float());

			if(layer.attribute("offset_x") && layer.attribute("offset_y"))
				screen[current_layer]->SetOffset(
					layer.attribute("offset_x").as_float(),
					layer.attribute("offset_y").as_float());

			if (layer.attribute("main").as_bool())
				main_layer = current_layer;

			current_layer++;
			max_layers++;
	}
}

Level::~Level()
{
	for (auto& it : screen){
		//liberar camadas  
	}
}

// void Level::update(float dt)
// {

// }

void Level::render(int layer)
{

	/* Forma temporária da implementação */
	if (layer == 5){
		for (int i = max_layers - 1; i >= 0; i--){
			screen[i]->Render();
		}
	}
	
	//tileMap_.renderLayer(layer, 0, 0);
	
	if (Resources::DEBUG_COLLISION && LAYER == 0)
		collisionMap_.render(0,0);

	/*
	 -- Forma final da implementação --
	if (layer < max_layers && layer >= 0)
		screen_layers[layer]->Render();
	*/
}


CollisionMap& Level::getCollisionMap()
{
	return collisionMap_;
}

/*std::vector<std::pair<int, TransformComponent*>> FirstLevel::createTerrain(unsigned int& nextId)
{
	std::vector<std::pair<int, TransformComponent*>> terrainEntities;
	for (int y = 0; y < collisionMap_.getHeight(); y++)
	{
		for (int x = 0; x < collisionMap_.getWidth(); x++)
		{
			if (collisionMap_.at(x, y) == 0)
			{
				terrainEntities.emplace_back( std::pair<int, TransformComponent*> (
					nextId++,
					new TransformComponent(Rect(
						x * Resources::TILE_WIDTH,
						y * Resources::TILE_HEIGHT,
						Resources::TILE_WIDTH,
						Resources::TILE_HEIGHT
					))
				));
			}
		}
	}

	return terrainEntities;
}*/
