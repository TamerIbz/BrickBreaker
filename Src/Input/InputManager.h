#pragma once
#include "../Main/main.h" 

class RENDER_GAME;
class RENDER_MAINMENU;

class InputManager
{
public:
	InputManager(Level* levelRef, Render* renderRef, FontManager* fontRef);
	void Input();
	void SetScaledMousePosition();
	void CheckUISelection();
	void RemoveUISelection();

	SDL_Point& GetMouseLocation() { return mouseLocation; };
	SDL_Point GetScaledMouseLocation;

private:
	SDL_Event event;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	SDL_Point mouseLocation;

public: // ref
	Player* player;
	Level* level;
	Render* render;
	FontManager* font;
};