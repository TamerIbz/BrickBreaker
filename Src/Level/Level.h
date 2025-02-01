#pragma once
#include "../Bricks/Brick.h"
#include "../Manager/GameManager.h"

#ifndef LEVEL_H
#define LEVEL_H
extern bool LEVELCOMPLETEINIT;
#endif

class GameManager;
class Brick;

class Level
{
public:
	Level(GameManager* managerRef);

	void CreateGameObjects();

	//levels
	void Level01();

	void RemoveBricks(int ID);

public:
	std::vector < std::shared_ptr<Barrier>> barrier;
	std::shared_ptr<Player> player;
	std::shared_ptr<Ball> ball;
	std::vector<std::shared_ptr<Brick>> brick;

private:
	GameManager* manager;

	int row = 0; // row
	int currentBrickPerRow = 0;
	int maxBrickPerRow = 0;

	int startXIndex = 0;
	int startYIndex = 0;

	int newXIndex = 0;
	int newYIndex = 0;
};