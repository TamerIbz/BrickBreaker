#pragma once
#include "SDL.h"
#include <iostream>
#include <vector>

#ifndef FPS_H
#define FPS_H
extern const float FPS;
extern const double TIME_STEP; // 0.016
extern const float MAX_FRAME_TIME;
extern const int FRAME_DELAY; // Milliseconds per frame
#endif

class FrameRate
{
private:
	Uint32 lastUpdate = SDL_GetTicks();
	Uint32 currentFrame = SDL_GetTicks();
	float accumulator = 0.0f;

public:
	void CurrentFrame();
	void FrameDelay();
	void SetFixedAccumulatorStep();

	float& GetAccumulator() { return accumulator; }
};