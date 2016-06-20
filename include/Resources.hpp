#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#ifdef __APPLE__
	#include <SDL2/SDL.h>
	#include <SDL2_image/SDL_image.h>
	#include <SDL2_mixer/SDL_mixer.h>
	#include <SDL2_ttf/SDL_ttf.h>
#else
	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_mixer.h"
	#include "SDL_ttf.h"
#endif

#include <unordered_map>
#include <string>
#include <memory>
#include "pugixml.hpp"
#include "music.hpp"

#define _attribute	pugi::xml_attribute
#define _node		pugi::xml_node
#define _document	pugi::xml_document
#define _parse		pugi::xml_parse_result


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
	static float PLAYER_ZIPLINE_SPEED;

	static int MAP_WIDTH;
	static int MAP_HEIGHT;

	static std::string TILE_SET_IMG;
	static std::string TILE_MAP_TXT;
	static std::string COLLISION_MAP_TXT;
	static std::string OBJECT_MAP_XML;
	static std::string GLOBAL_OBJECT_MAP_XML;

	static void Read(std::string filename_);
	//static void ReadVolumes(std::string filename_);

	// Global Values
	static std::unordered_map<std::string, int>			intTable;
	static std::unordered_map<std::string, float>		floatTable;

	// IMAGES
	static std::shared_ptr<SDL_Texture> GetImage(std::string file);
	static void ClearImages();

	// AUDIO
	static Mix_Chunk*					GetSound(std::string file);
	static void ClearSounds();

	// TEXT
	static std::shared_ptr<TTF_Font> GetFont(std::string file, int fontSize);
	static void ClearFonts();

private:
	static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> 	imageTable;
	static std::unordered_map<std::string, Mix_Chunk*> 						soundTable;
	static std::unordered_map<std::string, std::shared_ptr<TTF_Font>> 		fontTable;

	//static _document config;
};

#endif