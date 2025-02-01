#pragma once
#include "../GAME/GameObject.h"

class GameManager;

enum PlayerMovementDirection
{
	NONE,
	Left,
	Right,
	Up,
	Down
};

class Player : public GameObject
{
public:
	Player(GameManager* managerRef);

	void Movement();
	void Move(int direction);
	void MoveCollided(int overlapDirection);
	float GetOverlapDirection(SDL_Rect objA, SDL_Rect objB);
	void ChangeMovementDirection(PlayerMovementDirection direction);
	void Update() override;
	void PhysicsUpdate() override;
	void OnCollision(GameObject* col) override;
	void SetProperties() override;
	void Hit() override;

	bool CanBeRemoved(GameObject* obj) const override{return true;}

	const double movementSpeed = 375.0; // 10.0

private:
	PlayerMovementDirection MovementDirection = PlayerMovementDirection::NONE;
public:

	void SetOBJDimension(int height, int width) override
	{
		OBJHeight = height;
		OBJWidth = width;
	}

private: 
	GameManager* manager;
};
