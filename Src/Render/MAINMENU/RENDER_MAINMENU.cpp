#include "RENDER_MAINMENU.h"

#pragma region Render

bool RENDER_MAINMENU::RENDER_SCREEN(SDL_Surface* image)
{
    if (!RenderGraphics(image)) return false;
    if (!RenderTexts()) return false;

    return true;
}

bool RENDER_MAINMENU::RenderGraphics(SDL_Surface* image)
{
    if (!render) return false;
    if (!render->InitImage(BGPATH, image, bgRect, false, 0))  return false;
    return true;
}

#pragma region Render Text
bool RENDER_MAINMENU::RenderTexts()
{
    if (!font) return false;

    if (!font->RenderFont(PlayElement->FontType, Color_lightGray(), 
        PlayElement->FONT_TEXT, PlayElement->Font_rect, PlayElement->FONT_ID, textData, 
        TEXT_PIVOT::P_Center)) return false;

    if (!font->RenderFont(QuitElement->FontType, Color_lightGray(),
        QuitElement->FONT_TEXT, QuitElement->Font_rect, QuitElement->FONT_ID, 
        textData,TEXT_PIVOT::P_Center)) return false;
    return true;
}
#pragma endregion
#pragma endregion

#pragma region UI_Input
void RENDER_MAINMENU::HandleUIInput()
{
    if (CurrentSelectedButtonID == PlayElement->FONT_ID)
    {
        Play_UI();
    }
    else if (CurrentSelectedButtonID == QuitElement->FONT_ID)
    {
        Quit_UI();
    }
}

void RENDER_MAINMENU::Play_UI()
{
    AudioManager::getInstance().PlaySFX(BtnClick_SFX, 0);
    GAMEPLAYING = true;
    Menu_EventManager::getInstance().publish(SCREEN_STATES::GAME, SCREEN_STATES::MAINMENU);
    AudioManager::getInstance().PlaySFX(play_SFX, 0);
}

void RENDER_MAINMENU::Quit_UI()
{
    AudioManager::getInstance().PlaySFX(BtnClick_SFX, 0);
    GAMERUNNING = false;
}
#pragma endregion