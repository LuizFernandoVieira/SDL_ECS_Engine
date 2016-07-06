#ifndef	SCREENIMAGELAYER_HPP
#define	SCREENIMAGELAYER_HPP

#include <memory>

#ifdef __APPLE__
	#include <SDL2/SDL.h>
#else
	#include "SDL.h"
#endif


#include "ScreenLayer.hpp"


class ImageLayer : public ScreenLayer{
public:
	ImageLayer(const char* file);

	void Render();
	void open(const char* file);

	void setClip(int x, int y, int w, int h);

private:
	std::shared_ptr<SDL_Texture> texture_;
	SDL_Rect clipRect_;

	std::string filename_;
	int width_;
	int height_;
};

#endif