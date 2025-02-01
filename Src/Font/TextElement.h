#pragma once

#include "SDL.h"
#include "../../SDL_ttf.h"

class TextElement
{
public:
	TTF_Font* FontType;
	 int FONT_SIZE;
	const char* FONT_TEXT;
	const char* FONT_ID;
	SDL_Point Font_rect;

	TextElement(int font_size, const char* font_text, const char* font_id, SDL_Point& rect)
	{
		this->FONT_SIZE = font_size;
		this->FONT_TEXT = font_text;
		this->FONT_ID = font_id;
		this->Font_rect = rect;
	}
};