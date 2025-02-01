#pragma once
#include <SDL.h>
#include "SDL_image.h"
#include "SDL_surface.h"
#include "../GAME/GAMEINFO.h"
#include "../Font/FontManager.h"
#include "../Player/Player.h"
#include "../GAME/MENU_STATES.h"
#include "../Audio/AudioManager.h"

#ifndef RENDER_H
#define RENDER_H
extern bool RENDERCOMPLETEINIT;
#endif

class RENDER_GAME;
class RENDER_MAINMENU;
class RENDER_RETRYMENU;

class Render
{
public:
	~Render();
	Render(FontManager* font);

	bool InitializeScreen();
	bool RenderToScreen();

	bool InitRenderer();
	bool InitImage(const char* Path, SDL_Surface* Image, SDL_Rect& Rect, bool Rotate, int degrees);
	void RotateTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* dstRect, double angle);

	void CheckInputUI(SDL_Point& mouseLocation);
	void RemoveInputUI();
 
public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	SDL_Surface* image;

	// menus / screens
	RENDER_GAME* GameScreen = nullptr;
	RENDER_MAINMENU* MainMenuScreen = nullptr;
	RENDER_RETRYMENU* RetryMenuScreen = nullptr;

private:
	FontManager* font;
	AudioManager* audio;
};