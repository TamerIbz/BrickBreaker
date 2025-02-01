#include "RENDER_RETRYMENU.h"


#pragma region Render


bool RENDER_RETRYMENU::RENDER_SCREEN(SDL_Surface* image)
{
	if (!RenderGraphics(image)) return false;
	if (!RenderTexts()) return false;

	return true;
}

bool RENDER_RETRYMENU::RenderGraphics(SDL_Surface* image)
{
	if (!render) return false;
	if (!render->InitImage(BGPATH, image, bgRect, false, 0))  return false;
	return true;
}
#pragma region Render Text
bool RENDER_RETRYMENU::RenderTexts()
{
    if (!font) return false;

    if (!font->RenderFont(CurrentScoreElement->FontType, Color_white(),
        manager->Score.GetScoreText().c_str(), CurrentScoreElement->Font_rect, CurrentScoreElement->FONT_ID, textData,
        TEXT_PIVOT::P_Center)) return false;

    if (!font->RenderFont(HighScoreElement->FontType, Color_white(),
        manager->Score.GetHighscoreText().c_str(), HighScoreElement->Font_rect, HighScoreElement->FONT_ID,
        textData, TEXT_PIVOT::P_Center)) return false;

#pragma region Game_State_Text
    if (!font->RenderFont(GameStateElement->FontType, Color_white(),
        gameStateText.c_str(), GameStateElement->Font_rect, GameStateElement->FONT_ID,
        textData, TEXT_PIVOT::P_Center)) return false;
#pragma endregion

    if (!font->RenderFont(RetryElement->FontType, Color_white(),
        RetryElement->FONT_TEXT, RetryElement->Font_rect, RetryElement->FONT_ID,
        textData, TEXT_PIVOT::P_Center)) return false;

    if (!font->RenderFont(QuitElement->FontType, Color_white(),
        QuitElement->FONT_TEXT, QuitElement->Font_rect, QuitElement->FONT_ID,
        textData, TEXT_PIVOT::P_Center)) return false;
    return true;
}
#pragma endregion
#pragma endregion

#pragma region UI_Input
void RENDER_RETRYMENU::HandleUIInput()
{
    if (CurrentSelectedButtonID == RetryElement->FONT_ID)
        Retry_UI();

    if (CurrentSelectedButtonID == QuitElement->FONT_ID)
        Quit_UI();
}

void RENDER_RETRYMENU::Retry_UI()
{
    manager->Score.SetScoreValue(0);
    ONSTREAK = false;

    manager->RemoveALLGameobjects();
    level->CreateGameObjects();

    Menu_EventManager::getInstance().publish(SCREEN_STATES::GAME, SCREEN_STATES::RETRYMENU);
    CURRENTGAMESTATE = GAME_STATES::NONE_GS;

    AudioManager::getInstance().PlaySFX(BtnClick_SFX, 0);
    AudioManager::getInstance().PlaySFX(play_SFX, 0);

    GAMEPLAYING = true;
}
void RENDER_RETRYMENU::Quit_UI()
{
    AudioManager::getInstance().PlaySFX(BtnClick_SFX, 0);
    GAMERUNNING = false;
}
#pragma endregion