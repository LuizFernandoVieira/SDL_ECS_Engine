#include "../include/God.hpp"

God::God(float x, float y, TileMap& tileMap) : sprite_("../img/god.png")
{
	tileMap_ = &tileMap;
	rect_ = Rect(x, y, sprite_.getWidth(), sprite_.getHeight());
}

God::~God()
{

}

void God::update(float dt)
{

}

void God::render()
{
	sprite_.render(rect_.getX(), rect_.getY());
}

void God::moveTo(float x, float y)
{
	rect_.setX(x);
	rect_.setY(y);
}

void God::jump()
{

}

void God::placeTile(int x, int y)
{
	std::fstream fs;
	int mapWidth;
	int mapHeight;
	int mapDepth;
	char comma;

	fs.open("../map/tileMap.txt", std::fstream::in | std::fstream::out);

	if(!fs.is_open())
	{
		std::string fileStr("../map/tileMap.txt");
		//throw ExcecaoArquivo("Erro na abertura do arquivo de tile map " + fileStr);
		std::cout << "tileMap exception" << std::endl;
	}

	fs >> mapWidth;
	fs >> comma;
	fs >> mapHeight;
	fs >> comma;
	fs >> mapDepth;
	fs >> comma;

	int location = y*mapWidth + x + 0*mapWidth*mapHeight;
	int withComma = 3;
	int firstBreakLine = 2;

	fs.seekp(fs.tellg(), std::ios_base::beg);
	fs.seekp(location*withComma+firstBreakLine+y, std::ios_base::cur);

	fs << "02";

	fs.close();

	tileMap_->tileMatrix_[x + y*mapWidth + 0*mapWidth*mapHeight] = 02;
}

