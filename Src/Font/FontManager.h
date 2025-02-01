#pragma once

enum TEXT_PIVOT
{
	P_Center,
	P_Left,
	P_Right
};

#include "SDL.h"
#include "../../SDL_ttf.h"
#include "../Color/ColorManager.h"
#include "../GAME/GAMEINFO.h"
#include "../Manager/GameManager.h"
#include "TextElement.h"

#ifndef FONT_H
#define FONT_H
extern bool FONTCOMPLETEINIT;
#endif

struct TextData {
	const char* ID;
	const char* text;    // The text content
	SDL_Rect rect;       // Position and size of the text
	SDL_Texture* texture; // Texture for rendering
	bool isButton = false;
	bool isInitalized = false;

	void SetData(SDL_Rect& newRect, const char* newText, SDL_Texture* newTexture, bool isinit)
	{
		rect = newRect;
		text = newText;
		texture = newTexture;
		isInitalized = &isinit;
	}
};


class FontManager
{
public:
	FontManager(GameManager* managerRef);
	~FontManager()
	{
		TTF_Quit();
	}
	bool Init();
	void InitalizeFont(TTF_Font** font, const char* name, const int size);
	bool RenderFont(TTF_Font* font, SDL_Color color, const char*, SDL_Point pos, const char* textDataID, std::vector<TextData>& textData, TEXT_PIVOT textPivot);
	SDL_Rect* GetTextBoard() { return &TextBoard; }

private:
	SDL_Rect TextBoard;
	SDL_Surface* surface;
	SDL_Texture* texture;
public:
	GameManager* GetManager() { return manager; }

private:
	GameManager* manager;
};