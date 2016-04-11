#ifdef __APPLE__
	#include <SDL2_image/SDL_image.h>	
#else
	#include "SDL_image.h"
#endif

#include "../include/Resources.hpp"
#include "../include/Game.hpp"

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