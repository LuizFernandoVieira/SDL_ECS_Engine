#include <fstream>
#include <string>
#include <sstream>

#include "../include/Resources.hpp"
#include "../include/Game.hpp"

#define PRINTITALL 	true


int Resources::WINDOW_WIDTH 		= 0;
int Resources::WINDOW_HEIGHT 		= 0;
int Resources::TILE_WIDTH 			= 0;
int Resources::TILE_HEIGHT 			= 0;
int Resources::GRAVITY 				= 0; // pixels per second
float Resources::PLAYER_WALK_SPEED 	= 0; // pixels per second
float Resources::PLAYER_JUMP_SPEED 	= 0; // pixels per second

int Resources::MAP_WIDTH            = 0;
int Resources::MAP_HEIGHT           = 0;

std::string Resources::TILE_SET_IMG           = "../img/maps/test/tile_set.png";
std::string Resources::TILE_MAP_TXT           = "../map/tileMap.txt";
std::string Resources::COLLISION_MAP_TXT      = "../map/collisionMap.txt";
std::string Resources::OBJECT_MAP_XML         = "../map/objectMap.xml";
std::string Resources::GLOBAL_OBJECT_MAP_XML  = "../map/globalObjectMap.xml";


std::unordered_map<std::string, float> Resources::floatTable;
std::unordered_map<std::string, int> 	Resources::intTable;

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> 	Resources::imageTable;
std::unordered_map<std::string, Mix_Chunk*> 					Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> 		Resources::fontTable;






std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file)
{
	auto it = imageTable.find(file);

	if ( it == imageTable.end() ) {

		SDL_Texture* texture = IMG_LoadTexture ( Game::getInstance().getRenderer() , file.c_str() );

		if (texture == NULL) {
			std::cout << "Erro no carregamento da textura " << file << ": " << IMG_GetError() << std::endl;
		}

		auto deleteTexture = [] (SDL_Texture* texture)
		{
			SDL_DestroyTexture(texture);
		};
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


// FONT
std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int fontSize)
{
	std::ostringstream ss;
	ss << fontSize;
	auto it = fontTable.find(file + ss.str());

	if ( it == fontTable.end() )
	{
		// Nao achou musica na tabela, carrega
		TTF_Font* font = TTF_OpenFont(file.c_str(), fontSize);
		if (font == NULL)
		{
			std::cout << "Erro no carregamento da fonte " << file << ": " << TTF_GetError() << std::endl;
		}

		auto deleteFont = [] (TTF_Font* font)
		{
			TTF_CloseFont(font);
		};
		std::shared_ptr<TTF_Font> ptr (font, deleteFont);

		fontTable.emplace(file + ss.str(), ptr);
		return ptr;
	}
	else
	{
		// Musica ja está carregada, retorna ponteiro para ela
		std::shared_ptr<TTF_Font> font = it->second;
		return font;
	}
}

void Resources::ClearFonts()
{
	for ( auto it = fontTable.begin() ; it != fontTable.end(); ++it )
	{
		if (it->second.unique())
			fontTable.erase(it);
	}
}




void Resources::Read(std::string _filename){
		//for(pugi::xml_node tool = tools.first_child(); tool; tool = tool.next_sibling())

	int 			tempInt	= 0;
	float 			tempFloat;
	std::string		varName;
	std::string		varType;
	_document 	doc;
	_parse		config;

	config = doc.load_file(_filename.c_str());
	if (config.status){
		std::cout << "Error Reading CONFIG_FILE: " << config.description() << std::endl;
		std::cout << "\tStatus code: " << config.status << std::endl;
	}
	else std::cout << "Load result: " << config.description() << std::endl;
	std::cout << std::endl;


	_node node = doc.first_child();

	//std::cout << "First node name: [" << node.name() << "], node value: [" << node.first_child().name() << "]\n";
	//std::cout << "Second node name: [" << node.next_sibling().name() << "], node value: [" << node.next_sibling().first_child().name() << "]\n";

	//Fetching Globals
	for(_node data = node.child("globals").first_child(); data; data = data.next_sibling()){
		std::cout << "count: " << tempInt << "\t";
		tempInt++;

		varName = data.attribute("name").value();
		varType = data.attribute("type").value();


		if (varType == "int"){
			intTable.emplace(varName, 		data.attribute("value").as_int());
			std::cout << "Fetched value: " << varName << " = " << intTable[varName] << std::endl;
		}else{
			floatTable.emplace(varName, 	data.attribute("value").as_float());
			std::cout << "Fetched value: " << varName << " = " << floatTable[varName] << std::endl;
		}
	}
	std::cout << std::endl;


	//Assossiação de Valores (Temporário, substituir por função getValue)
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

}