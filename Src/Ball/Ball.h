#pragma once
#include "../GAME/GameObject.h"

class GameManager;

//Timer startTimer(5000);

class Ball : public GameObject
{
public:
	Ball(GameManager* managerRef);
	void Update() override;
	void PhysicsUpdate() override;
	void OnCollision(GameObject* col) override;
	void HittingObjects(GameObject* _object);
	void SetProperties() override;
	void SetInitialMov();
	void Bounce(GameObject* col);
	void ReflectBounce(float& velocityX, float& velocityY, float normalX, float normalY);
	void Hit() override;
	void CheckPositionNOTSame(GameObject* _object);
	void AddANDCheckPositionIndex(int& index);
	void SetPositionChecker(std::vector<int>& pos, int& checkerIndex, int axis);
	void RandomiseRandomPositionRandomly(); // Randomly randomise position so game because unpredictable and more fun
	void OnFinishTimer();
	bool CanBeRemoved(GameObject* obj) const override
	{
		return true;
	}

	bool DeathPosCheck()
	{
		return GetRect().y + GetRect().h >= HEIGHT;
	}

	void SetOBJDimension(int height, int width) override
	{
		OBJHeight = height;
		OBJWidth = width;
	}

private:
	const double initialMovSpeed = 350.0; // 375,0
	bool initialCollision = false;

	int initialYPos = (HEIGHT) - 95; // 500


#pragma region Velocity
	float velocityX = 0.0f;
	float velocityY = 0.0f;
#pragma endregion

#pragma region Checking x / y positions so we dont have the same movement
	std::vector<int> CurrentXPositionChecker; //only size 2
	int currentXPositionCheckerIndex = 0;

	std::vector<int> CurrentYPositionChecker; //only size 2
	int currentYPositionCheckerIndex = 0;
#pragma endregion

private:
	GameManager* manager;

	//sounds
	Mix_Chunk* hit_SFX;
	Mix_Chunk* start_SFX;
	Mix_Chunk* die_SFX;
}; 
