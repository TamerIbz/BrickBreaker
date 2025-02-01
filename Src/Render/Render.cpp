#include "Render.h"
#include "GAME/RENDER_GAME.h"
#include "MAINMENU/RENDER_MAINMENU.h"
#include "RETRYMENU/RENDER_RETRYMENU.h"

bool RENDERCOMPLETEINIT = false;
enum SCREEN_STATES CURRENT_SCREEN_STATE = SCREEN_STATES::MAINMENU;
SDL_Renderer* GLOBALRENDERER;

Render::~Render()
{
    if (this->GameScreen)
        GameScreen->~RENDER_GAME();
    if (this->MainMenuScreen)
        MainMenuScreen->~RENDER_MAINMENU();
    if (this->RetryMenuScreen)
        RetryMenuScreen->~RENDER_RETRYMENU();
}

Render::Render(FontManager* fontRef) : font(fontRef)
{ 
    this->GameScreen = new RENDER_GAME(this, font, font->GetManager(), font->GetManager()->level);
    this->MainMenuScreen = new RENDER_MAINMENU(this, font,font->GetManager(), font->GetManager()->level);
    this->RetryMenuScreen = new RENDER_RETRYMENU(this, font,font->GetManager(), font->GetManager()->level);

    Menu_EventManager::getInstance().publish(SCREEN_STATES::MAINMENU, SCREEN_STATES::MAINMENU);
}

#pragma region Rendering
bool Render::InitializeScreen()
{
    switch (CURRENT_SCREEN_STATE)
    {
    case SCREEN_STATES::MAINMENU:  if (!MainMenuScreen->RENDER_SCREEN(image)) return false; break;
    case SCREEN_STATES::RETRYMENU: if (!RetryMenuScreen->RENDER_SCREEN(image)) return false; break;
    case SCREEN_STATES::GAME:       if (!GameScreen->RENDER_SCREEN(image)) return false; break;
    }

    if (!RENDERCOMPLETEINIT)
        RENDERCOMPLETEINIT = !RENDERCOMPLETEINIT;

    return true;
}

bool Render::RenderToScreen()
{
    SDL_RenderClear(renderer);
    if (!InitializeScreen()) return false;
    SDL_RenderPresent(renderer);
    return true;
}

#pragma region Init Checking
bool Render::InitRenderer()
{
#pragma region SDL INIT 
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Failed to initialize SDL VIDEO: " << SDL_GetError() << std::endl;
        return false;
    }
    else
        std::cerr << "Initialize SDL VIDEO" << std::endl;
#pragma endregion

#pragma region Creating Window
    window = SDL_CreateWindow("Brick Breaker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }
    else
        std::cerr << "Window Created" << std::endl;
#pragma endregion

#pragma region Creating Renderer
    renderer = SDL_CreateRenderer(window, -1, 0);
    GLOBALRENDERER = renderer;
    if (!renderer)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    else
        std::cerr << "Renderer Created" << std::endl;
#pragma endregion
    return true;
}

bool Render::InitImage(const char* Path, SDL_Surface* Image, SDL_Rect& Rect, bool Rotate, int degrees)
{
#pragma region Check Image INIT
     if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))  
    {
        std::cout << "Image Failed to initialize" << IMG_GetError() << std::endl;;
        return false;
    }
#pragma endregion
     Image = IMG_Load(Path);
#pragma region Check Image path
    if (!Image)
    {
        std::cout << "Image can not display, maybe check the path!" << IMG_GetError << std::endl;
        std::cout << Path;
        return false;
    }
#pragma endregion

    if(texture)
        SDL_DestroyTexture(texture);

    texture = SDL_CreateTextureFromSurface(renderer, Image);
    SDL_FreeSurface(Image);

#pragma region Check Texture
    if (!texture)
    {
        std::cerr << "Cannot load texture " << SDL_GetError() << std::endl;;
        return false;
    }
#pragma endregion

    if (!Rotate)
        SDL_RenderCopy(renderer, texture, NULL, &Rect);
    else
    {
        RotateTexture(renderer, texture, &Rect, degrees);
    }

    return true;
}
void Render::RotateTexture(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect* dstRect, double angle)
{
    SDL_Point pivot = { 0, 0 };
    SDL_RenderCopyEx(renderer, texture, nullptr, dstRect, angle, &pivot, SDL_FLIP_NONE);
}
#pragma endregion
#pragma endregion

#pragma region UI
void Render::CheckInputUI(SDL_Point& mouseLocation)
{
    switch (CURRENT_SCREEN_STATE)
    {
    case SCREEN_STATES::MAINMENU:  MainMenuScreen->CheckButtonOnClick(mouseLocation); break;
    case SCREEN_STATES::RETRYMENU:RetryMenuScreen->CheckButtonOnClick(mouseLocation); break;
    case SCREEN_STATES::GAME: GameScreen->CheckButtonOnClick(mouseLocation); break;
    }
}

void Render::RemoveInputUI()
{
    switch (CURRENT_SCREEN_STATE)
    {
    case SCREEN_STATES::MAINMENU:  MainMenuScreen->RemoveUIINPUT(); break;
    case SCREEN_STATES::RETRYMENU: RetryMenuScreen->RemoveUIINPUT();  break;
    case SCREEN_STATES::GAME: MainMenuScreen->RemoveUIINPUT(); break;
    }
}
#pragma endregion

