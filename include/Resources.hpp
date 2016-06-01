#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#ifdef __APPLE__
	#include <SDL2/SDL.h>
#else
	#include "SDL.h"
#endif

#include <unordered_map>
#include <string>
#include <sstream>
#include <memory>

auto deleteTexture = [] (SDL_Texture* texture)
{
	SDL_DestroyTexture(texture);
};

class Resources
{
public:
	//GLOBALS
	static int WINDOW_WIDTH;
	static int WINDOW_HEIGHT;
	static int TILE_WIDTH;
	static int TILE_HEIGHT;

	static int GRAVITY;

	static float PLAYER_WALK_SPEED;
	static float PLAYER_JUMP_SPEED;

	static void Read(std::string filename_);

	//Global Values
	static std::unordered_map<std::string, int>			intTable;
	static std::unordered_map<std::string, float>		floatTable;

	//IMAGES
	static std::shared_ptr<SDL_Texture> GetImage(std::string file);
	static void ClearImages();

	//AUDIO
	static std::unordered_map<std::string, Mix_Chunk*> 		soundTable;
	static void ClearAudio();


private:
	static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
};

#endif