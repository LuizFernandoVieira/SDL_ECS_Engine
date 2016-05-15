#include "../include/CollisionMap.hpp"
#include "../include/Game.hpp"
#include "../include/Globals.hpp"

CollisionMap::CollisionMap(const char* file) : filename_(file)
{
	load();
}


void CollisionMap::load()
{
	collisionMatrix_.clear();

	std::ifstream ifs;
	char comma;

	ifs.open(filename_, std::ifstream::in);

	if(!ifs.is_open())
	{
		std::cout << "Erro na abertura do arquivo de collision map para leitura" << std::endl;
	}

	ifs >> mapWidth_;
	ifs >> comma;
	ifs >> mapHeight_;
	ifs >> comma;

	int curValue;

	while(ifs.good())
	{
		ifs >> curValue;
		ifs >> comma;
		collisionMatrix_.emplace_back(curValue);
	}

	ifs.close();
}

void CollisionMap::save()
{
	std::ofstream ofs(filename_, std::ofstream::out | std::ofstream::trunc);
	if(!ofs.is_open())
	{
		std::cout << "Erro na abertura do arquivo de collision map para escrita" << std::endl;
	}

	ofs << mapWidth_;
	ofs << ',';
	ofs << mapHeight_;
	ofs << ',';

	ofs << std::endl;
	ofs << std::endl;

	for (int y = 0; y < mapHeight_; y++)
	{
		for (int x = 0; x < mapWidth_; x++)
		{
			// to_string
			std::ostringstream ss;
			int value = at(x, y);
			ss << value;
			std::string strValue = ss.str();
			if(value >= 0 && value < 10) {
				strValue = "0" + strValue;
			}
			ofs << strValue;
			ofs << ',';
		}
		ofs << std::endl;
	}

	ofs.close();
}


int& CollisionMap::at(int x, int y)
{
	return collisionMatrix_[ x + y*mapWidth_ ];
}


void CollisionMap::render(int x, int y)
{
	for (int i = 0; i < mapHeight_; i++) {
		for (int j = 0; j < mapWidth_; j++) {
			if (at(j, i) >= 0) {
				renderSelection(Rect(
					j * Globals::TILE_WIDTH + x, 
					i * Globals::TILE_HEIGHT + y, 
					Globals::TILE_WIDTH, 
					Globals::TILE_HEIGHT
				));
			}
		}
	}
}

void CollisionMap::renderSelection(Rect rect)
{
	SDL_Renderer* renderer = Game::getInstance().getRenderer();
	SDL_RenderDrawLine(renderer, rect.x(), rect.y(), rect.w() + rect.x(), rect.y());
	SDL_RenderDrawLine(renderer, rect.x(), rect.y(), rect.x(), rect.h() + rect.y());
	SDL_RenderDrawLine(renderer, rect.x(), rect.y(), rect.w() + rect.x(), rect.h() + rect.y());
	SDL_RenderDrawLine(renderer, rect.w() + rect.x(), rect.y(), rect.w() + rect.x(), rect.h() + rect.y());
	SDL_RenderDrawLine(renderer, rect.x(), rect.h() + rect.y(), rect.w() + rect.x(), rect.h() + rect.y());
	SDL_RenderDrawLine(renderer, rect.w() + rect.x(), rect.y(), rect.x(), rect.h() + rect.y());
}

int CollisionMap::getWidth() const
{
	return mapWidth_;
}

int CollisionMap::getHeight() const
{
	return mapHeight_;
}