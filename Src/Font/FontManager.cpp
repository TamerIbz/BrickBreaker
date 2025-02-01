#include "FontManager.h"

bool FONTCOMPLETEINIT = false;

FontManager::FontManager(GameManager* managerRef) : manager(managerRef)
{;
Init();
}

bool FontManager::Init()
{
    if (TTF_Init() < 0)
    {
        std::cout << "TTF NOT WORKING" << TTF_GetError() << std::endl;
        FONTCOMPLETEINIT = false;
        return false;
    }
    std::cout << "Font Initialized" << std::endl;
    FONTCOMPLETEINIT = true;
    return true;
}

void FontManager::InitalizeFont(TTF_Font** font, const char* name, const int size)
{
    *font = TTF_OpenFont(name, size);
}

bool FontManager::RenderFont(TTF_Font* font, SDL_Color color, const char* text, SDL_Point pos, const char* textDataID, std::vector<TextData>& textData, TEXT_PIVOT textPivot)
{
    if (!GLOBALRENDERER || !font) return false;

    const char* t = text;
    surface = TTF_RenderText_Solid(font, t, color); 
    texture = SDL_CreateTextureFromSurface(GLOBALRENDERER, surface);

    if (!surface || !texture) return false;

    const int height_padding = 10;

    TextBoard.w = surface->w;
    TextBoard.h = surface->h;

    switch (textPivot)
    {
    case TEXT_PIVOT::P_Center:
        TextBoard.x = pos.x - (TextBoard.w / 2);  // Center horizontally
        TextBoard.y = pos.y - (TextBoard.h / 2) - height_padding;  // Center vertically
        break;
        
    case TEXT_PIVOT::P_Left: // pivot to left, so nums get pushed to right
        TextBoard.x = pos.x;
        TextBoard.y = pos.y - (TextBoard.h - height_padding);
        break;
    case TEXT_PIVOT::P_Right: // pivot to right, so nums get pushed to left
        TextBoard.x = pos.x - TextBoard.w;
        TextBoard.y = pos.y - (TextBoard.h - height_padding);
        break;

    }
  
    for (auto& texts : textData)
    {;
        if (texts.ID != textDataID) continue;
        if (texts.isInitalized) continue;

        texts.SetData(TextBoard, text, texture, true);
   }

    SDL_RenderCopy(GLOBALRENDERER, texture, NULL, &TextBoard);
    SDL_FreeSurface(surface); 
    SDL_DestroyTexture(texture);

    return true;
}

