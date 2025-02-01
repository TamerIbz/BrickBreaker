#include "AudioManager.h"

bool AUDIOCOMPLETEINIT = false;

AudioManager::AudioManager()
{
	InitAudio();
}

void AudioManager::InitAudio()
{
#pragma region INIT AUDIO
	if (SDL_INIT_AUDIO < 0)
	{
		std::cerr << "Failed to initialize SDL AUDIO: " << SDL_GetError() << std::endl;
		AUDIOCOMPLETEINIT = false;
		return;
	}
	else
		std::cerr << "Initialize SDL AUDIO" << std::endl;
#pragma endregion

#pragma region OPEN AUDIO
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << ("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		AUDIOCOMPLETEINIT = false;
		return;
	}
	else
		std::cerr << "AUDIO has been opened" << std::endl;
#pragma endregion

	AUDIOCOMPLETEINIT = true;
}
