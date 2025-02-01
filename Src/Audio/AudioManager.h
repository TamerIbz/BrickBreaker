#pragma once
#include "SDL.h"
#include "SDL_mixer.h"
#include "iostream"


#ifndef AUDIO_H
#define AUDIO_H
extern bool AUDIOCOMPLETEINIT;
#endif

class AudioManager
{
public:
#pragma region Load

	void LoadMusic(Mix_Music*& _music, const char* path)
	{
		_music = Mix_LoadMUS(path);
	}
	void LoadSFX(Mix_Chunk*& sfx, const char* path)
	{
		sfx = Mix_LoadWAV(path);
	}
#pragma endregion

#pragma region Play
	void PlayMusic(Mix_Music* _music, int loopIndex)
	{
		Mix_PlayMusic(_music, loopIndex);
	}
	void PlaySFX(Mix_Chunk* _sfx, int loopIndex)
	{
		Mix_PlayChannel(-1, _sfx, loopIndex);
	}
#pragma endregion

#pragma region Stop
	void StopMusic()
	{
		Mix_HaltMusic();
	}
#pragma endregion

public:
	static AudioManager& getInstance() {
		static AudioManager instance;
		return instance;
	}

	AudioManager();
	~AudioManager()
	{
		Mix_CloseAudio();
		Mix_Quit();
	}

private:
	void InitAudio();

};