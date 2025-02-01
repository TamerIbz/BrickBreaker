#pragma once
#include "../Collision/Barrier/Barrier.h"
#include "../Score/ScoreManager.h"
#include "../Live/LiveManager.h"
#include "../Player/Player.h"
#include "../Ball/Ball.h"
#include "../Bricks/Brick.h"
#include "../Level/Level.h"
#include "../Events/Menu_EventManager.h"

class Level;
class Player;
class Ball;
class Brick;

class GameManager
{
public:
	GameManager();

	int& BRICKCOUNT() { return brickCount; }
	bool CheckGameOVER() { return brickCount <= 0; }
	void GameOver(GAME_STATES gameState);

	void RemoveALLGameobjects();
	
	ScoreManager Score;
	Level* level;
private:
	int brickCount = 0;
};