#include "main.h"
GAME_STATES CURRENTGAMESTATE = GAME_STATES::NONE_GS;

Main mainVar;
GameManager manager;
Level level(&manager);
//AudioManager audio;
FontManager font(&manager);
Render renderer(&font);
FrameRate fps;
InputManager input(&level, &renderer, &font);

Timer startDelayTimer(.75f);

int main(int argc, char* argv[])
{
    if (!renderer.InitRenderer()) return -1;
    if (!renderer.InitializeScreen())
    {
        mainVar.QUIT_GAME(renderer.texture, renderer.renderer, renderer.window);
        return -1;
    }
    if (!LEVELCOMPLETEINIT && !RENDERCOMPLETEINIT && !FONTCOMPLETEINIT && !AUDIOCOMPLETEINIT) 
    {
        std::cerr << "LEVEL || RENDER || FONT || AUDIO COULD NOT COMPLETE" << std::endl;
        mainVar.QUIT_GAME(renderer.texture, renderer.renderer, renderer.window);
        return -1;
    }

    mainVar.RenderScreen();

    while (GAMERUNNING)
    {
        fps.CurrentFrame();
        input.Input();

#pragma region Update Methods
        while (fps.GetAccumulator() >= TIME_STEP)
        {
            for (const auto& instance : GameObject::getRegistry())
            {
                if (!CURRENT_SCREEN_STATE == SCREEN_STATES::GAME) continue;
                instance->Update();  // Fixed logic update
                instance->PhysicsUpdate();
            }
            fps.SetFixedAccumulatorStep();
        }
#pragma endregion

        mainVar.RenderScreen();
        fps.FrameDelay();
    }

    mainVar.QUIT_GAME(renderer.texture, renderer.renderer, renderer.window);
 
    return 0;
}

void Main::RenderScreen()
{
    if (!renderer.RenderToScreen()) GAMERUNNING = false; 
}

void Main::QUIT_GAME(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Window* window)
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

}