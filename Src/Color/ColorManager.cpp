#include "ColorManager.h"

SDL_Color Color_red()
{
	return SETRGB(255, 0, 81);
}

SDL_Color Color_lightGray()
{
	return SETRGB(160, 160, 160);
}

SDL_Color Color_darkGray()
{
	return SETRGB(75, 75, 75);
}

SDL_Color Color_lightOrange()
{
	return SETRGB(230, 85, 62);
}

SDL_Color Color_white()
{
	return SETRGB(255, 255, 255);
}

SDL_Color SETRGB(int r, int g, int b)
{
	SDL_Color color;
	color.r = r, color.g = g, color.b = b;
	return color;
}
