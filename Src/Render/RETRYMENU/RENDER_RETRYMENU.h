#pragma once
#include "../RENDER_BASE_MENU.h"

class RENDER_RETRYMENU : public RENDER_BASE_MENU
{
public:
	~RENDER_RETRYMENU()
	{
#pragma region Close Texts
		if (CurrentScoreElement && CurrentScoreElement->FontType)
			TTF_CloseFont(CurrentScoreElement->FontType);

		if (HighScoreElement && HighScoreElement->FontType)
			TTF_CloseFont(HighScoreElement->FontType);

		if (GameStateElement && GameStateElement->FontType)
			TTF_CloseFont(GameStateElement->FontType);

		if (RetryElement && RetryElement->FontType)
			TTF_CloseFont(RetryElement->FontType);

		if (QuitElement && QuitElement->FontType)
			TTF_CloseFont(QuitElement->FontType);
#pragma endregion
	}

	RENDER_RETRYMENU(Render* _render, FontManager* _font, GameManager* _manager, Level* _level) : RENDER_BASE_MENU(SCREEN_STATES::RETRYMENU) {
		render = _render;
		font = _font;
		manager = _manager;
		level = _level;

		// INIT TEXT ELEMENT
		this->CurrentScoreElement = new TextElement(86, "", "CURRENT_SCORE_ID", SetTextPos(WIDTH / 2, (HEIGHT / 2) - 120));
		this->HighScoreElement = new TextElement(24, "", "HIGHSCORE_ID", SetTextPos(WIDTH / 2, (HEIGHT / 2) - 55));
		this->GameStateElement = new TextElement(42, "", "GAME_STATE_ID", SetTextPos(WIDTH / 2, (HEIGHT / 2) - 250));
		this->RetryElement = new TextElement(38, "RETRY", "RETRY_ID", SetTextPos(WIDTH / 2, (HEIGHT / 2) + 120));
		this->QuitElement = new TextElement(32, "QUIT", "QUIT_ID", SetTextPos(WIDTH / 2, (HEIGHT / 2) + 180));

		// INIT FONT
		font->InitalizeFont(&CurrentScoreElement->FontType, "Fonts/fSCORE.ttf", CurrentScoreElement->FONT_SIZE);
		font->InitalizeFont(&HighScoreElement->FontType, "Fonts/fSCORE.ttf", HighScoreElement->FONT_SIZE);
		font->InitalizeFont(&GameStateElement->FontType, "Fonts/fSCORE.ttf", GameStateElement->FONT_SIZE);
		font->InitalizeFont(&RetryElement->FontType, "Fonts/fButton01.ttf", RetryElement->FONT_SIZE);
		font->InitalizeFont(&QuitElement->FontType, "Fonts/fButton01.ttf", QuitElement->FONT_SIZE);

		// ADD DATA TO TEXT_DATA ARRAY
		textData.push_back({ CurrentScoreElement->FONT_ID, " ",emptyRect, NULL, false, false });
		textData.push_back({ HighScoreElement->FONT_ID, " ", emptyRect, NULL, false, false });
		textData.push_back({ GameStateElement->FONT_ID, " ", emptyRect, NULL, false, false });
		textData.push_back({ RetryElement->FONT_ID, " ", emptyRect, NULL, true, false });
		textData.push_back({ QuitElement->FONT_ID, " ", emptyRect, NULL, true, false });

		//Load AUDIO
		AudioManager::getInstance().LoadMusic(BgMusic, "Assets/Audio/Music/BG_MM_MUS.wav");
		AudioManager::getInstance().LoadSFX(lose_SFX, "Assets/Audio/SFX/GAME/GameOver.wav");
		AudioManager::getInstance().LoadSFX(win_SFX, "Assets/Audio/SFX/GAME/GameWin.wav");
		AudioManager::getInstance().LoadSFX(play_SFX, "Assets/Audio/SFX/GAME/GameStart.wav");
		SetBGPATH("Assets/Bg/Retry_BG.png");

		manager = font->GetManager();
		level = font->GetManager()->level;
	}
	bool RENDER_SCREEN(SDL_Surface* image) override;
	bool RenderGraphics(SDL_Surface* image) override;
	bool RenderTexts() override;
	void HandleUIInput() override;
	void OnScreenActive() override
	{
		AudioManager::getInstance().PlayMusic(BgMusic, -1);

		switch (CURRENTGAMESTATE)
		{
		case GAME_STATES::NONE_GS:
			gameStateText = "";
			break;
		case GAME_STATES::WIN:
			gameStateText = "WINNER!!!";
			AudioManager::getInstance().PlaySFX(win_SFX, 0);
			break;

		case GAME_STATES::LOSE:
			gameStateText = "LOSER!!!";
			AudioManager::getInstance().PlaySFX(lose_SFX, 0);
			break;
		}
	}
	void OnScreenDeactive() override
	{
		AudioManager::getInstance().StopMusic();
	}

	void Retry_UI();
	void Quit_UI();

private:
	TextElement* CurrentScoreElement;
	TextElement* HighScoreElement;
	TextElement* GameStateElement;
	TextElement* RetryElement;
	TextElement* QuitElement;

	std::string gameStateText;

	//sound
	Mix_Chunk* lose_SFX;
	Mix_Chunk* win_SFX;
	Mix_Chunk* play_SFX;
};