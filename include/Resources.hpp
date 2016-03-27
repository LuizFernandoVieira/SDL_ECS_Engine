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
	static std::shared_ptr<SDL_Texture> GetImage(std::string file);
	static void ClearImages();
private:
	static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
};

#endif