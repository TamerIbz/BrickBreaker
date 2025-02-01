#pragma once
#include "SDL.h"
#include "../GAME/GAMEINFO.h"

static class POSITION
{
public:
	static SDL_Rect& RESET_POSITION(SDL_Rect& RECT, SDL_Point RESET_RECT)
	{
		RECT.x = RESET_RECT.x;
		RECT.y = RESET_RECT.y;

		return RECT;
	}

	static bool CHECK_OFFSCREEN_POSITION(SDL_Rect& RECT)
	{
		return ((RECT.x + RECT.w) >= WIDTH) || ((RECT.y + RECT.h) >= HEIGHT) || (RECT.x <= 0) || (RECT.y <= 0);
	}
};
