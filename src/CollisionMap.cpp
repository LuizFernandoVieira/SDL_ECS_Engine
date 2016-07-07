#include "../include/CollisionMap.hpp"
#include "../include/Game.hpp"
#include "../include/Resources.hpp"
#include "../include/Camera.hpp"

CollisionMap::CollisionMap(const char* file) : filename_(file)
{
	load();
}

CollisionMap::CollisionMap(const char* file, int width, int height) : filename_(file)
{
	newMap(width, height);
}


void CollisionMap::newMap(int width, int height)
{
	collisionMatrix_.clear();

	mapWidth_ = width;
	mapHeight_ = height;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			collisionMatrix_.emplace_back(-1);
		}
	}

	save();
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
				renderSelection(at(j, i), Rect(
					j * Resources::TILE_WIDTH + x - Camera::pos_.x(), 
					i * Resources::TILE_HEIGHT + y - Camera::pos_.y(), 
					Resources::TILE_WIDTH, 
					Resources::TILE_HEIGHT
				));
			}
		}
	}
}

void CollisionMap::renderSelection(int collision, Rect rect)
{
	// SDL_Renderer* renderer = Game::getInstance().getRenderer();
/*	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, rect.x(), rect.y(), rect.w() + rect.x(), rect.y());
	SDL_RenderDrawLine(renderer, rect.x(), rect.y(), rect.x(), rect.h() + rect.y());
	SDL_RenderDrawLine(renderer, rect.x(), rect.y(), rect.w() + rect.x(), rect.h() + rect.y());
	SDL_RenderDrawLine(renderer, rect.w() + rect.x(), rect.y(), rect.w() + rect.x(), rect.h() + rect.y());
	SDL_RenderDrawLine(renderer, rect.x(), rect.h() + rect.y(), rect.w() + rect.x(), rect.h() + rect.y());
	SDL_RenderDrawLine(renderer, rect.w() + rect.x(), rect.y(), rect.x(), rect.h() + rect.y());*/
	std::string file;
	switch (collision)
	{
		case 0:
			file = "../img/interface/editor/colisao_chao.png";
			break;
		case 1:
			file = "../img/interface/editor/colisao_teto.png";
			break;
		case 2:
			file = "../img/interface/editor/colisao_parede.png";
			break;
		case 3:
			file = "../img/interface/editor/colisao_teto_chao.png";
			break;
		case 4:
			file = "../img/interface/editor/colisao_completa.png";
			break;
		case 5:
			file = "../img/interface/editor/btn_collision_1.png";
			break;
		case 6:
			file = "../img/interface/editor/btn_collision_2.png";
			break;
		case 7:
			file = "../img/interface/editor/colisao_morte.png";
			break;
	}
	std::shared_ptr<SDL_Texture> texture = Resources::GetImage(file.c_str());
	SDL_Rect clipRect, dstRect;

	clipRect.x = 0;
	clipRect.y = 0;
	clipRect.w = rect.w();
	clipRect.h = rect.h();
	dstRect.x = rect.x();
	dstRect.y = rect.y();
	dstRect.w = rect.w();
	dstRect.h = rect.h();

	SDL_SetTextureAlphaMod(texture.get(), 80);
	SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND);
	SDL_RenderCopy( Game::getInstance().getRenderer(), texture.get(), &clipRect, &dstRect );
}

int CollisionMap::getWidth() const
{
	return mapWidth_;
}

int CollisionMap::getHeight() const
{
	return mapHeight_;
}