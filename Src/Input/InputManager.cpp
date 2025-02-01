#include "InputManager.h"
#include "../Render/GAME/RENDER_GAME.h"
#include "../Render/MAINMENU/RENDER_MAINMENU.h"

InputManager::InputManager(Level* levelRef, Render* renderRef, FontManager* fontRef) : level(levelRef), render(renderRef), font(fontRef)
{
    player = levelRef->player.get();
}

void InputManager::Input()
{
    if (player != level->player.get())
        player = level->player.get();

    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)  GAMERUNNING = false;
        if (keystates[SDL_SCANCODE_ESCAPE]) GAMERUNNING = false;
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            // press mouse button down
            SetScaledMousePosition();
            CheckUISelection();
        }
        else if (event.type == SDL_MOUSEBUTTONUP)
        {
            // release mouse button 
            RemoveUISelection();
        }

        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.scancode == SDL_SCANCODE_A)
                player->ChangeMovementDirection(PlayerMovementDirection::Left);
            else  if (event.key.keysym.scancode == SDL_SCANCODE_D)
                player->ChangeMovementDirection(PlayerMovementDirection::Right);
            else  if (event.key.keysym.scancode == SDL_SCANCODE_W)
                player->ChangeMovementDirection(PlayerMovementDirection::Up);
            else  if (event.key.keysym.scancode == SDL_SCANCODE_S)
                player->ChangeMovementDirection(PlayerMovementDirection::Down);
        }
        else if (event.type == SDL_KEYUP)
        {
            if (event.key.keysym.scancode == SDL_SCANCODE_A)
                player->ChangeMovementDirection(PlayerMovementDirection::NONE);
            else if (event.key.keysym.scancode == SDL_SCANCODE_D)
                player->ChangeMovementDirection(PlayerMovementDirection::NONE);
            else  if (event.key.keysym.scancode == SDL_SCANCODE_W)
                player->ChangeMovementDirection(PlayerMovementDirection::NONE);
            else  if (event.key.keysym.scancode == SDL_SCANCODE_S)
                player->ChangeMovementDirection(PlayerMovementDirection::NONE);
        }
    }
}

#pragma region Mouse Position
void InputManager::SetScaledMousePosition()
{
    int windowWidth, windowHeight;
    SDL_GetWindowSize(render->window, &windowWidth, &windowHeight);

    float scaleX = static_cast<float>(WIDTH) / windowWidth;
    float scaleY = static_cast<float>(HEIGHT) / windowHeight;

    SDL_GetMouseState(&mouseLocation.x, &mouseLocation.y);

    int scaledMouseX = static_cast<int>(mouseLocation.x * scaleX);
    int scaledMouseY = static_cast<int>(mouseLocation.y * scaleY);
    GetScaledMouseLocation.x = scaledMouseX;
    GetScaledMouseLocation.y = scaledMouseY;
}
#pragma endregion

#pragma region UI
void InputManager::CheckUISelection()
{
    render->CheckInputUI(GetScaledMouseLocation);
}

void InputManager::RemoveUISelection()
{
    render->RemoveInputUI();
}
#pragma endregion
