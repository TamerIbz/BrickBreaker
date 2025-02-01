#include "GameManager.h"
#include "cmath"


GameManager::GameManager()
{
}

#pragma region GameOver
void GameManager::GameOver(GAME_STATES gameState)
{
	Score.SetHighscore();
	CURRENTGAMESTATE = gameState;
	Menu_EventManager::getInstance().publish(SCREEN_STATES::RETRYMENU, SCREEN_STATES::GAME);

	GAMEPLAYING = false;
}
#pragma endregion

#pragma region Removing all gameobjects
void GameManager::RemoveALLGameobjects()
{
	for (const auto& instance : GameObject::getRegistry())
	{
		instance->RemoveFromRegistry(false);
	}
	
	level->brick.clear();
	level->barrier.clear();
}
#pragma endregion