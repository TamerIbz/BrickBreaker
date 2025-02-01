#include "Level.h"

bool LEVELCOMPLETEINIT = false;

Level::Level(GameManager* managerRef) : manager(managerRef)
{
	manager->level = this;
	CreateGameObjects();
}

void Level::CreateGameObjects()
{
	Level01();
#pragma region  Creating Barriers
	const int barrierWidth = 10; // 10
	const int barrierOffset = 35; // 35

	const int size = 703; // 650 // 715
	const int ySize = round(533.157 / 10.0) * 10; // 533.157

	barrier.push_back(std::make_shared<Barrier>(barrierOffset, (HEIGHT - size / 1.1f) / 2, barrierWidth, size, false, 0, manager));  // left
	barrier.push_back(std::make_shared<Barrier>((WIDTH - barrierWidth) - barrierOffset, (HEIGHT - size / 1.1f) / 2, barrierWidth, size, false, 0, manager)); // right
	//barrier = std::make_shared<Barrier>((WIDTH - ySize) / 2, (HEIGHT)-50, barrierWidth, ySize, true, -90, manager); // bottom

	barrier.push_back(std::make_shared<Barrier>((WIDTH - ySize) / 2, (60), barrierWidth, ySize, true, -90, manager)); // top

#pragma endregion

#pragma region Player
	player = std::make_shared<Player>(manager);

#pragma endregion

#pragma region Ball
	ball = std::make_shared<Ball>(manager); // RENDER ANYTHING WITH COLLISION ABOVE 
#pragma endregion

	LEVELCOMPLETEINIT = true;
}

#pragma region Level
void Level::Level01()
{
	//std::cout << "MI";
	row = 0;
	currentBrickPerRow = 0;
	maxBrickPerRow = 12;

	startXIndex = 54; // start index
	startYIndex = 150; // start index
	newXIndex = startXIndex; // current index
	newYIndex = startYIndex; // current index
	for (int i = 0; i < 36; i++)
	{
		currentBrickPerRow++;
		brick.push_back(std::make_shared<Brick>(newXIndex, newYIndex, manager));
		brick[i]->ID = i;
		manager->BRICKCOUNT()++;

		// Set Rect
#pragma region Positioning
		newXIndex += brick[i]->GetRect().w + 1; // 60/70 debug // 50 perfect
		//bw // bo
		if (newXIndex >= ((WIDTH - 15) - 35) - brick[i]->GetRect().w)
			//if (newXIndex >= WIDTH - 20)
		{
			newYIndex += brick[i]->GetRect().h + 1;
			newXIndex = startXIndex; // 54
		}
#pragma endregion

#pragma region Row & Textures
		switch (row)
		{
		case 0:brick[i]->SetPath("Assets/Brick/Grey_B.png"); brick[i]->GetLives().AddLives(3); break;
		case 1:brick[i]->SetPath("Assets/Brick/Orange_B.png");  brick[i]->GetLives().AddLives(2); break;
		case 2:brick[i]->SetPath("Assets/Brick/Green_B.png"); brick[i]->GetLives().AddLives(1); break;
		}
		if (currentBrickPerRow >= maxBrickPerRow)
		{
			currentBrickPerRow = 0;
			row++;
		}
#pragma endregion

	}
}
#pragma endregion


void Level::RemoveBricks(int ID)
{
	for (auto it = brick.begin(); it != brick.end();)
	{
		std::shared_ptr<Brick> thing = *it;

		if (thing->ID != ID)
		{
			++it; // Move to the next element if no erasure happens
			continue;
		}
		it = brick.erase(it);
		manager->BRICKCOUNT()--;
		break; // Exit the loop after erasing
	}

	if (manager->CheckGameOVER())
	{
		if (!GAMEPLAYING) return;
		manager->GameOver(GAME_STATES::WIN);
	}
}
