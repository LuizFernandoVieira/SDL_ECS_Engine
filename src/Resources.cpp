#ifdef __APPLE__
	#include <SDL2_image/SDL_image.h>	
#else
	#include "SDL_image.h"
#endif

#include <fstream>
#include "../include/Resources.hpp"
#include "../include/Game.hpp"

#define PRINTITALL false

std::unordered_map<std::string, float> Resources::floatTable;
std::unordered_map<std::string, int> 	Resources::intTable;

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file)
{
	auto it = imageTable.find(file);

	if ( it == imageTable.end() ) {

		SDL_Texture* texture = IMG_LoadTexture ( Game::getInstance().getRenderer() , file.c_str() );

		if (texture == NULL) {
			std::cout << "Erro no carregamento da textura" << std::endl;
			std::string imgError = IMG_GetError();
			//throw ExcecaoTextura( "Erro no carregamento da textura " + file + '\n' + imgError );
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



void Resources::Read(std::string filename_){
	std::ifstream config;
	config.open(filename_, std::ifstream::in);


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
		if (tempName[0] == '/')
			if (tempName[1] == '*')
				continue;


		//Tipo: int
		if (tempName == "#INT")
		{
			config >> tempName;	//Nome da primeira variável
			while (tempName[0] != '#')
			{
				config >> tempInt;		//Valor Inteiro
				intTable.emplace(tempName, tempInt);
				if (PRINTITALL) std::cout << tempName << " = " << tempInt << std::endl;

				config >> tempName;		//Nome da próxima variável
			}

			continue;
		}

		//Tipo: float
		if (tempName == "#FLOAT")
		{
			config >> tempName;	//Nome da primeira variável
			while (tempName[0] != '#')
			{
				config >> tempFloat;		//Valor Inteiro
				if (PRINTITALL) std::cout << tempName << " = " << tempFloat << std::endl;
				floatTable.emplace(tempName, tempFloat);

				config >> tempName;			//Nome da próxima variável
			}

			continue;
		}

		//Tipo: Imagem
		if (tempName == "#IMAGE")
		{
			config >> tempName;	//Nome da primeira variável
			while (tempName[0] != '#')
			{
				if (GetImage(tempName) != nullptr)
				{
					if (PRINTITALL) std::cout << tempName << "Loaded Successfully" << std::endl;
				}
				else
				{
					std::cout << tempName << "Could not be loaded" << std::endl;
				}
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
		std::cout << "Value WINDOW_WIDTH now equals: " 	<< intTable["WINDOW_WIDTH"] << std::endl;
		std::cout << "Value WINDOW_HEIGHT now equals: " << intTable["WINDOW_HEIGHT"] << std::endl;
		std::cout << "Value TILE_WIDTH now equals: " 	<< intTable["TILE_WIDTH"] << std::endl;
		std::cout << "Value TILE_HEIGHT now equals: " 	<< intTable["TILE_HEIGHT"] << std::endl;
		std::cout << "Value GRAVITY now equals: " 		<< intTable["GRAVITY"] << std::endl << std::endl;

		std::cout << "Value PLAYER_JUMP_SPEED now equals: " << floatTable["PLAYER_JUMP_SPEED"] << std::endl;
		std::cout << "Value PLAYER_WALK_SPEED now equals: " << floatTable["PLAYER_WALK_SPEED"] << std::endl;
	}

	//intTable.clear();
	//floatTable.clear();
}