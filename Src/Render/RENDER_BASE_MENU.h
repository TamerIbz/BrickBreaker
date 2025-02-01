#pragma once
#include <SDL.h>
#include "SDL_image.h"
#include "SDL_surface.h"
#include "SDL_mixer.h"
#include "../GAME/GAMEINFO.h"
#include "../GAME/GameObject.h"
#include "Render.h"
#include "../Font/FontManager.h"
#include "../Audio/AudioManager.h"
#include "../Events/Menu_EventManager.h"

class Render;
class FontManager;

class RENDER_BASE_MENU
{
public:
	virtual ~RENDER_BASE_MENU()
	{
		for (auto& Tdata : textData)
		{
			if (Tdata.texture == nullptr) continue;
			SDL_DestroyTexture(Tdata.texture);
		}

		textData.clear();
	}

	RENDER_BASE_MENU(SCREEN_STATES screen) : screenType(screen) 
	{

		AudioManager::getInstance().LoadSFX(BtnClick_SFX,"Assets/Audio/SFX/UI/Click_SFX.wav");
		// subscribing to events
		Menu_EventManager::getInstance().subscribeActivate("ScreenActivate", [this](SCREEN_STATES currentScreen) {
			if (currentScreen == screenType) {
				OnScreenActive();
			}
			});

		Menu_EventManager::getInstance().subscribeDeactivate("ScreenDeactivate", [this](SCREEN_STATES previousScreen) {
			if (previousScreen == screenType) {
				OnScreenDeactive();
			}
			});
	}

	virtual bool RENDER_SCREEN(SDL_Surface* image) = 0;
	virtual bool RenderGraphics(SDL_Surface* image) = 0;
	virtual bool RenderTexts() = 0;
	virtual void OnScreenActive() = 0;
	virtual void OnScreenDeactive() = 0;

#pragma region Button Logic
	bool CheckClickButtonRect(SDL_Point& mouseVector, TextData& buttons)
	{
		if( mouseVector.x > buttons.rect.x && mouseVector.x < (buttons.rect.x + buttons.rect.w)
			&&
			mouseVector.y > buttons.rect.y && mouseVector.y < (buttons.rect.y + buttons.rect.h))
		{
			return true;
		}

		return false;
	}

	void CheckButtonOnClick(SDL_Point& mouseVector)
	{
		if (CurrentSelectedButtonID != nullptr) return; // stops buttons getting called more then once
		for (auto& buttons : textData)
		{
			if (!buttons.isButton) continue;
			if (!buttons.isInitalized) continue;

			if (CheckClickButtonRect(mouseVector, buttons))
			{
				CurrentSelectedButtonID = buttons.ID;
				HandleUIInput();
			}
			
		}
	}
#pragma endregion

	void RemoveUIINPUT() { CurrentSelectedButtonID = nullptr; }
	virtual void HandleUIInput() = 0;

protected:
	//ref
	 Render* render;
	 FontManager* font;
	 GameManager* manager;
	 Level* level;

	 SDL_Rect emptyRect = { 0,0,0,0 };
	 const char* CurrentSelectedButtonID;

	 // buttons
	 std::vector<TextData> textData;
	 SDL_Point& SetTextPos(int x, int y)
	 {
		 SDL_Point newpoint;
		 newpoint.x = x;
		 newpoint.y = y;
		 return newpoint;
	 }

	 SCREEN_STATES screenType;

protected:
	 // Set bg rect & bg path
	 const char* BGPATH = nullptr;
	 SDL_Rect bgRect = { 0, 0, WIDTH, HEIGHT }; // every menu will need a background
	 void SetBGPATH(const char* newpath) { BGPATH = newpath; } // could have a base properties override/abstract method

	 Mix_Music* BgMusic; // Base Music Value
	 Mix_Chunk* BtnClick_SFX;
};