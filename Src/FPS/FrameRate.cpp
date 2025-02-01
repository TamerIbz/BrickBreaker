#include "FrameRate.h"

const float FPS = 60.0f;
const double TIME_STEP = 1.0f / FPS;
const float MAX_FRAME_TIME = 0.25f;
const int FRAME_DELAY = 1000 / 60;

void FrameRate::CurrentFrame()
{
    Uint32 frameStart = SDL_GetTicks(); // Start of the frame
    currentFrame = SDL_GetTicks();
    float frameTime = (currentFrame - lastUpdate) / 1000.0f; // Time in seconds
    lastUpdate = currentFrame;

    // Cap frame time to prevent spiral of death
    if (frameTime > MAX_FRAME_TIME) {
        frameTime = MAX_FRAME_TIME;
    }

    accumulator += frameTime;
}

void FrameRate::FrameDelay()
{
    Uint32 frameEnd = SDL_GetTicks();
    float elapsedFrameTime = (frameEnd - currentFrame) / 1000.0f;
    if (elapsedFrameTime < TIME_STEP)
    {
        SDL_Delay((TIME_STEP - elapsedFrameTime) * 1000);
    }
}

void FrameRate::SetFixedAccumulatorStep()
{
    accumulator -= TIME_STEP;
}
