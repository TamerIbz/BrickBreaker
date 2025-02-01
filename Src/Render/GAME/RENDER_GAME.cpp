#include "RENDER_GAME.h"
//#include "../Render.h"

#pragma region Render Graphics

bool RENDER_GAME::RENDER_SCREEN(SDL_Surface* image)
{
    if (!RenderGraphics(image)) return false;
    if (!RenderTexts()) return false;

    return true;
}
 
bool RENDER_GAME::RenderGraphics(SDL_Surface* image)
{
    if (!render) return false;
    if (!render->InitImage(BGPATH , image, bgRect, false, 0))  return false;
    for (const auto& instance : GameObject::getRegistry())
    {
        if (!render->InitImage(instance->GetPath(), instance->GetImage(), instance->GetRect(), instance->Rotate, instance->Degrees))
            return false;
    }		

    return true;
}

#pragma region Render Text
bool RENDER_GAME::RenderTexts()
{
    if (!font)
        return false;

    if (!font->RenderFont(ScoreElement->FontType, Color_white(),
       manager->Score.GetScoreText().c_str(), ScoreElement->Font_rect, ScoreElement->FONT_ID, 
        textData,TEXT_PIVOT::P_Right)) return false; // RENDER SCORE

    if (!font->RenderFont(LiveElement->FontType, Color_red(),
        level->ball->GetLives().GetLiveText().c_str(), LiveElement->Font_rect,LiveElement->FONT_ID, textData, 
        TEXT_PIVOT::P_Left)) return false; // RENDER LIVES

    return true;
}
#pragma endregion
#pragma endregion

#pragma region UI_Input
void RENDER_GAME::HandleUIInput()
{
 
}
#pragma endregion