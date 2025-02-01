#pragma once
#include "../RENDER_BASE_MENU.h"

class RENDER_MAINMENU : public RENDER_BASE_MENU
{
public:
	~RENDER_MAINMENU() 
	{
#pragma region Close Texts
		if (PlayElement && PlayElement->FontType)
			TTF_CloseFont(PlayElement->FontType);

		if (QuitElement && QuitElement->FontType)
			TTF_CloseFont(QuitElement->FontType);
#pragma endregion
	}

	RENDER_MAINMENU(Render* _render, FontManager* _font, GameManager* _manager, Level* _level) : RENDER_BASE_MENU(SCREEN_STATES::MAINMENU)
	{
		render = _render;
		font = _font;
		manager = _manager;
		level = _level;

		// INIT TEXT ELEMENT
		this->PlayElement = new TextElement(52, "PLAY", "PLAY_ID", SetTextPos(WIDTH / 2, HEIGHT / 2));
		this->QuitElement = new TextElement(40, "QUIT", "QUIT_ID", SetTextPos(WIDTH / 2, (HEIGHT / 2) + 60));

		// INIT FONT
		font->InitalizeFont(&PlayElement->FontType, "Fonts/fButton01.ttf", PlayElement->FONT_SIZE);
		font->InitalizeFont(&QuitElement->FontType, "Fonts/fButton01.ttf", QuitElement->FONT_SIZE);

		// ADD DATA TO TEXT_DATA ARRAY
		textData.push_back({ PlayElement->FONT_ID, "", emptyRect, nullptr, true, false });
		textData.push_back({ QuitElement->FONT_ID, "", emptyRect, nullptr, true, false });

		//Load AUDIO
		AudioManager::getInstance().LoadMusic(BgMusic, "Assets/Audio/Music/BG_MM_MUS.wav");
		AudioManager::getInstance().LoadSFX(play_SFX, "Assets/Audio/SFX/GAME/GameStart.wav");

		SetBGPATH("Assets/Bg/MM_Bg.png");

	}
//	void Initialize() override;
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

	// UI MENUS
	void Play_UI();
	void Quit_UI();

private:
	TextElement* PlayElement;
	TextElement* QuitElement;

	Mix_Chunk* play_SFX;
};