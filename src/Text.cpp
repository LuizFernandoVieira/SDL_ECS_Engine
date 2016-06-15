#include "../include/Text.hpp"
#include "../include/Game.hpp"
#include "../include/Camera.hpp"
#include "../include/Resources.hpp"


Text::Text(	std::string fontFile,
			int fontSize,
			TextStyle style,
			std::string text,
			SDL_Color color,
			int x, int y)
{
	this->fontSize = fontSize;
	font = Resources::GetFont(fontFile, fontSize);
	this->style = style;
	this->text = text;
	this->color = color;
	box.x(x);
	box.y(y);
	texture = NULL;
	remakeTexture();
}


Text::~Text()
{
	if (texture != NULL)
		SDL_DestroyTexture(texture);
}


void Text::render()
{
	SDL_Rect srcRect, dstRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = box.w();
	srcRect.h = box.h();

	dstRect.x = box.x() - Camera::pos_.x();
	dstRect.y = box.y() - Camera::pos_.y();
	dstRect.w = box.w();
	dstRect.h = box.h();

	//std::cout << scaleX << ", " << scaleY << std::endl;

	SDL_RenderCopy ( Game::getInstance().getRenderer(), texture, &srcRect, &dstRect);
}


void Text::setPos(int x, int y, bool centerX, bool centerY)
{
	box.x( centerX ? x - box.w() / 2 : x );
	box.y( centerY ? y - box.h() / 2 : y );
}

void Text::setText(std::string text)
{
	this->text = text;
	remakeTexture();
}

void Text::setColor(SDL_Color color)
{
	this->color = color;
	remakeTexture();
}

void Text::setStyle(TextStyle style)
{
	this->style = style;
	remakeTexture();
}

void Text::setFontSize(int fontSize)
{
	this->fontSize = fontSize;
	remakeTexture();
}

std::string Text::getText()
{
	return text;
}

Rect& Text::getPos()
{
	return box;
}


void Text::remakeTexture()
{
	int w, h;
	SDL_Surface* surface;
	SDL_Color black;
	black.r = 0;
	black.g = 0;
	black.b = 0;

	switch(this->style)
	{
		case SOLID:
			surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
			break;
		case SHADED:
			surface = TTF_RenderText_Shaded(font.get(), text.c_str(), this->color, black);
			break;
		case BLENDED:
			surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
			break;
	}

	texture = SDL_CreateTextureFromSurface(Game::getInstance().getRenderer(), surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	box.w(w);
	box.h(h);
}