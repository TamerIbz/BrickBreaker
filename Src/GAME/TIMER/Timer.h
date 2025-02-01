#pragma once
#include <SDL.h>
#include <functional>
//#include <iostream>

class Timer
{
public:
	Timer(float _maxTime) : maxTime(_maxTime * 1000)
	{
	}

	// Countdown
	void SetTimerCountdown()
	{
		if (!isCounting || isFinished) return;

		Uint32 currentTime = SDL_GetTicks();
		Uint32 elapsedTime = currentTime - startTime;

		if (elapsedTime <= maxTime)
			return;

		isCounting = false;
		isFinished = true;

		if (onFinish) onFinish();
	}

#pragma region Initial Set & Reset Timer
	void SetTimer(std::function<void()> callback)
	{
		ResetTimer();

		startTime = SDL_GetTicks();
		isCounting = true;
		isFinished = false;

		onFinish = callback;
	}

	void ResetTimer()
	{
		isCounting = false;
		isFinished = false;
		startTime = 0;
	}
#pragma endregion

	// is counting ref
	bool IsCounting() const { return isCounting; }
	bool IsFinished() const { return isFinished; }
	
private:
	Uint32 startTime = SDL_GetTicks();
	Uint32 maxTime = 0; //1450

	bool isCounting = false;
	bool isFinished = false;

	std::function<void()> onFinish;
};
