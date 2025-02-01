#pragma once
#include "SDL.h"
#include "../../SDL_ttf.h"
#include "../Render/Render.h"
#include "../GAME/GAMEINFO.h"
#include "../FPS/FrameRate.h"
#include "../Font/FontManager.h"
#include "../Color/ColorManager.h"
#include "../Input/InputManager.h"
#include "../Level/Level.h"
#include "../GAME/MENU_STATES.h"
#include "../GAME/GAME_STATES.h"
#include "../Audio/AudioManager.h"
#include <iostream>
#include <vector>

class Main
{
public:
	void RenderScreen();
	void QUIT_GAME(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Window* window);
};