#pragma once
#include "../RENDER_BASE_MENU.h"

class RENDER_GAME : public RENDER_BASE_MENU
{
public:
	~RENDER_GAME() 
	{
#pragma region Close Texts
		if (ScoreElement && ScoreElement->FontType)
			TTF_CloseFont(ScoreElement->FontType);

		if (LiveElement && LiveElement->FontType)
			TTF_CloseFont(LiveElement->FontType);
#pragma endregion

#pragma region Close Audio
		if (BgMusic)
			Mix_FreeMusic(BgMusic);
#pragma endregion

	}

	RENDER_GAME(Render* _render, FontManager* _font, GameManager* _manager, Level* _level) : RENDER_BASE_MENU(SCREEN_STATES::GAME) {
		render = _render;
		font = _font;
		manager = _manager;
		level = _level;

		// INIT TEXT ELEMENT
		this->ScoreElement = new TextElement(32, " ", "SCORE_ID", SetTextPos(WIDTH - 50, HEIGHT));
		this->LiveElement = new TextElement(26, " ", "LIVE_ID", SetTextPos(50, HEIGHT - 12));

		// INIT FONT
		font->InitalizeFont(&ScoreElement->FontType, "Fonts/fSCORE.ttf", ScoreElement->FONT_SIZE);
		font->InitalizeFont(&LiveElement->FontType, "Fonts/fLIVE.ttf", LiveElement->FONT_SIZE);

		// ADD DATA TO TEXT_DATA ARRAY
		textData.push_back({ ScoreElement->FONT_ID, " ",emptyRect, NULL, false, false});
		textData.push_back({ LiveElement->FONT_ID, " ", emptyRect, NULL, false, false});

		//Load AUDIO
		AudioManager::getInstance().LoadMusic(BgMusic, "Assets/Audio/Music/BG_GAME_MUS.wav");

		SetBGPATH("Assets/Bg/Game_Bg.png");
	}

	//void Initialize() override;
    bool RENDER_SCREEN(SDL_Surface* image) override;
	bool RenderGraphics(SDL_Surface* image) override;
	bool RenderTexts() override;
	void HandleUIInput() override;
	void OnScreenActive() override
	{
		AudioManager::getInstance().PlayMusic(BgMusic, -1);
	}
	void OnScreenDeactive() override
	{
		AudioManager::getInstance().StopMusic();
	}
private:
	TextElement* ScoreElement;
	TextElement* LiveElement;
};