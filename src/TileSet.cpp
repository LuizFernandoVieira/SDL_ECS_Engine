#include "../include/TileSet.hpp"

TileSet::TileSet(int tileWidth, int tileHeight, const char* file)
{
	tileWidth_ 	= tileWidth;
	tileHeight_ = tileHeight;

	try {
		tileSet_ = new Sprite(file);
		rows_ 		= (int) (tileSet_->getHeight()/tileHeight_);
		columns_ 	= (int) (tileSet_->getWidth()/tileWidth_);
	} catch(std::exception& ex) {
		std::cout << "tileSet exception" << std::endl;
		//throw ex;
	}
}

void TileSet::render(unsigned index, float x, float y)
{
	if(index > rows_*columns_) {
		//throw std::invalid_argument("Indice muito grande para o numero de tiles");
		std::cout << "Indice muito grande para o numero de tiles" << std::endl;
		std::cout << "index: " << index << std::endl;
		std::cout << "rows*cols: " << rows_*columns_ << std::endl;
	}

	tileSet_->setClip( 
		(index%columns_) * tileWidth_,
		(int)(index/columns_) * tileHeight_,
	 	tileWidth_, tileHeight_ 
	);
	tileSet_->render(x, y);
}

int TileSet::getTileWidth() const
{
	return tileWidth_;
}

int TileSet::getTileHeight() const
{
	return tileHeight_;
}