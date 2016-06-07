#ifdef __APPLE__
	#include <SDL2_image/SDL_image.h>
	#include <SDL2_mixer/SDL_mixer.h>
#else
	#include "SDL_image.h"
	#include "SDL_mixer.h"
#endif

#include <fstream>
#include <string>
#include "../include/Resources.hpp"
#include "../include/Game.hpp"
#include "../include/pugixml.hpp"

#define PRINTITALL 	true
#define LINE_BREAK	'#'
#define	CONFIG_FILE	"../config.xml"

#define _attribute	pugi::xml_attribute
#define _node		pugi::xml_node
#define _document	pugi::xml_document

std::unordered_map<std::string, float> Resources::floatTable;
std::unordered_map<std::string, int> 	Resources::intTable;

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> 	Resources::imageTable;
std::unordered_map<std::string, Mix_Chunk*> 					Resources::soundTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file)
{
	auto it = imageTable.find(file);

	if ( it == imageTable.end() ) {

		SDL_Texture* texture = IMG_LoadTexture ( Game::getInstance().getRenderer() , file.c_str() );

		if (texture == NULL) {
			std::cout << "Erro no carregamento da textura " << file << ": " << IMG_GetError() << std::endl;
		}

		std::shared_ptr<SDL_Texture> ptr (texture, deleteTexture);

		imageTable.emplace(file, ptr);
		return ptr;
	} else {
		std::shared_ptr<SDL_Texture> texture = it->second;
		return texture;
	}
}

void Resources::ClearImages()
{
	for ( auto it = imageTable.begin() ; it != imageTable.end(); ++it ) {
		if (it->second.unique()) {
			imageTable.erase(it);
		}
	}
}





//Sound
Mix_Chunk* Resources::GetSound(std::string file){
	std::unordered_map<std::string, Mix_Chunk*>::iterator asset;
	asset = soundTable.find(file);

	if (asset == soundTable.end()){
		asset = (soundTable.emplace(file, Mix_LoadWAV(file.c_str()))).first;
		std::cout << "new sound loaded: " << file << std::endl;
	}

	if (asset->second == nullptr){
		std::cout << "Error while loading \"" << file << "\": file could not be retrieved!" << std::endl;
		std::cout << "\t SDL_mixer error: " << Mix_GetError() << std::endl;
	}
	return asset->second;
}

void	Resources::ClearSounds(){
	soundTable.clear();
}




// ----------------------------------------------------------

void Resources::Read(std::string filename_){
	std::ifstream config;
	config.open(filename_, std::ifstream::in);

	/*	TODO
		- Para fazer o carregamento a partir de nomes abstratos ("CHAR_JUMP", "ENEMY_ATTACK", etc.),
			será necessária uma hash table intermediária, para associar os nomes aos endereços em disco,

	std::unordered_map<std::string, std::string> image_names;
	*/


	//Valores Intermediários
	int 			tempInt;
	float 			tempFloat;
	std::string		tempName;

	if(!config.is_open())
	{
		std::cout << "Erro na abertura do arquivo de globals para leitura" << std::endl;
		return;
	}

	//Aquisição de Valores
	config >> tempName;
	while(config.good())
	{

		//Parsing: Comentários
		if (tempName[0] != LINE_BREAK){
			std::getline(config, tempName);
			config >> tempName;
				continue;
		}


		//Tipo: int
		if (tempName == "#INT")
		{
			config >> tempName;	//Nome da primeira variável
			while (tempName[0] != LINE_BREAK)
			{
				config >> tempInt;		//Valor Inteiro
				intTable.emplace(tempName, tempInt);
				config >> tempName;		//Nome da próxima variável
			}

			continue;
		}

		//Tipo: float
		if (tempName == "#FLOAT")
		{
			config >> tempName;	//Nome da primeira variável
			while (tempName[0] != LINE_BREAK)
			{
				config >> tempFloat;		//Valor Inteiro
				floatTable.emplace(tempName, tempFloat);
				config >> tempName;			//Nome da próxima variável
			}

			continue;
		}

		//Tipo: Imagem
		if (tempName == "#IMAGE")
		{
			config >> tempName;	//Nome da primeira variável
			while (tempName[0] != LINE_BREAK)
			{
				config >> tempName;			//Nome da próxima variável
			}

			continue;
		}

		//Tipo: Música
		if (tempName == "#MUSIC")
		{
			config >> tempName;	//Nome da primeira variável
			while (tempName[0] != LINE_BREAK)
			{
				config >> tempName;			//Nome da próxima variável
			}

			continue;
		}

		config >> tempName;
	}

	config.close();

	//Assossiação de Valores
	WINDOW_WIDTH 		= intTable["WINDOW_WIDTH"];
	WINDOW_HEIGHT 		= intTable["WINDOW_HEIGHT"];
	TILE_WIDTH 			= intTable["TILE_WIDTH"];
	TILE_HEIGHT 		= intTable["TILE_HEIGHT"];
	GRAVITY 			= intTable["GRAVITY"];

	PLAYER_JUMP_SPEED 	= floatTable["PLAYER_JUMP_SPEED"];
	PLAYER_WALK_SPEED 	= floatTable["PLAYER_WALK_SPEED"];



	//Test Printing
	if (PRINTITALL){

		std::cout << "Float Values:" << std::endl;
		for ( auto it = floatTable.begin(); it != floatTable.end(); ++it)
			std::cout << "\t" << it->first << " : " << it->second << std::endl;
		std::cout << std::endl;


		std::cout << "Int Values:" << std::endl;
		for ( auto it = intTable.begin(); it != intTable.end(); ++it)
			std::cout << "\t" << it->first << " : " << it->second << std::endl;
		std::cout << std::endl;


		std::cout << "Images:" << std::endl;
		for ( auto it = imageTable.begin(); it != imageTable.end(); ++it){
			std::cout << "\t" << it->first;
			if (it->second == nullptr)
				std::cout << "Failure" << std::endl;
			else std::cout << "Success" << std::endl;
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << "Resources Loaded Successfully" << std::endl;

	//image_names.clear();
}

void Resources::xmlRead(std::string filename_){
	_document config;
	if (!config.load_file(CONFIG_FILE))
		std::cout << "Error Reading CONFIG_FILE: File could not be found" << std::endl;

	int 			tempInt;
	float 			tempFloat;
	std::string		tempName;


	WINDOW_WIDTH 		= intTable["WINDOW_WIDTH"];
	WINDOW_HEIGHT 		= intTable["WINDOW_HEIGHT"];
	TILE_WIDTH 			= intTable["TILE_WIDTH"];
	TILE_HEIGHT 		= intTable["TILE_HEIGHT"];
	GRAVITY 			= intTable["GRAVITY"];

	PLAYER_JUMP_SPEED 	= floatTable["PLAYER_JUMP_SPEED"];
	PLAYER_WALK_SPEED 	= floatTable["PLAYER_WALK_SPEED"];


/*

	//Valores Intermediários
	int 			tempInt;
	float 			tempFloat;
	std::string		tempName;

	if(!config.is_open())
	{
		std::cout << "Erro na abertura do arquivo de globals para leitura" << std::endl;
		return;
	}

	//Aquisição de Valores
	config >> tempName;
	while(config.good())
	{

		//Parsing: Comentários
		if (tempName[0] != LINE_BREAK){
			std::getline(config, tempName);
			config >> tempName;
				continue;
		}


		//Tipo: int
		if (tempName == "#INT")
		{
			config >> tempName;	//Nome da primeira variável
			while (tempName[0] != LINE_BREAK)
			{
				config >> tempInt;		//Valor Inteiro
				intTable.emplace(tempName, tempInt);
				config >> tempName;		//Nome da próxima variável
			}

			continue;
		}

		//Tipo: float
		if (tempName == "#FLOAT")
		{
			config >> tempName;	//Nome da primeira variável
			while (tempName[0] != LINE_BREAK)
			{
				config >> tempFloat;		//Valor Inteiro
				floatTable.emplace(tempName, tempFloat);
				config >> tempName;			//Nome da próxima variável
			}

			continue;
		}

		//Tipo: Imagem
		if (tempName == "#IMAGE")
		{
			config >> tempName;	//Nome da primeira variável
			while (tempName[0] != LINE_BREAK)
			{
				config >> tempName;			//Nome da próxima variável
			}

			continue;
		}

		//Tipo: Música
		if (tempName == "#MUSIC")
		{
			config >> tempName;	//Nome da primeira variável
			while (tempName[0] != LINE_BREAK)
			{
				config >> tempName;			//Nome da próxima variável
			}

			continue;
		}

		config >> tempName;
	}

	config.close();

	//Assossiação de Valores
	WINDOW_WIDTH 		= intTable["WINDOW_WIDTH"];
	WINDOW_HEIGHT 		= intTable["WINDOW_HEIGHT"];
	TILE_WIDTH 			= intTable["TILE_WIDTH"];
	TILE_HEIGHT 		= intTable["TILE_HEIGHT"];
	GRAVITY 			= intTable["GRAVITY"];

	PLAYER_JUMP_SPEED 	= floatTable["PLAYER_JUMP_SPEED"];
	PLAYER_WALK_SPEED 	= floatTable["PLAYER_WALK_SPEED"];



	//Test Printing
	if (PRINTITALL){

		std::cout << "Float Values:" << std::endl;
		for ( auto it = floatTable.begin(); it != floatTable.end(); ++it)
			std::cout << "\t" << it->first << " : " << it->second << std::endl;
		std::cout << std::endl;


		std::cout << "Int Values:" << std::endl;
		for ( auto it = intTable.begin(); it != intTable.end(); ++it)
			std::cout << "\t" << it->first << " : " << it->second << std::endl;
		std::cout << std::endl;


		std::cout << "Images:" << std::endl;
		for ( auto it = imageTable.begin(); it != imageTable.end(); ++it){
			std::cout << "\t" << it->first;
			if (it->second == nullptr)
				std::cout << "Failure" << std::endl;
			else std::cout << "Success" << std::endl;
		}
		std::cout << std::endl;
	}

	std::cout << std::endl << "Resources Loaded Successfully" << std::endl;

	//image_names.clear();
*/
}
