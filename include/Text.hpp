#ifndef TEXT_H
#define TEXT_H

#ifdef __APPLE__
	#include <SDL2_ttf/SDL_ttf.h>
	#include <SDL2/SDL.h>
#else
	#include "SDL_ttf.h"
	#include "SDL.h"
#endif

#include <string>
#include <memory>

#include "Rect.hpp"


namespace Colors {
	static SDL_Color black = {0, 0, 0, 255};
	static SDL_Color white = {255, 255, 255, 0};
	static SDL_Color blue = {0, 0, 255, 255};
}

class Text
{
public:
	enum TextStyle { SOLID, SHADED, BLENDED };

	Text(	std::string fontFile,
			int fontSize,
			TextStyle style,
			std::string text,
			SDL_Color color,
			int x = 0,
			int y = 0);

	~Text();

	void render();

	void setPos(int x, int y, bool centerX = true, bool centerY = true);
	void setText(std::string text);
	void setColor(SDL_Color color);
	void setStyle(TextStyle style);
	void setFontSize(int fontSize);

	std::string getText();
	Rect& getPos();

private:
	void remakeTexture();

	std::shared_ptr<TTF_Font> font;
	SDL_Texture* texture;

	std::string text;
	TextStyle style;
	int fontSize;
	SDL_Color color;
	Rect box;
};


#endif // TEXT_H