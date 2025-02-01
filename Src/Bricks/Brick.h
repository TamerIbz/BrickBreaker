#pragma once
#include "../Manager/GameManager.h" 
#include "../GAME/GameObject.h"

class GameManager;

class Brick : public GameObject
{
public:
	Brick(int xpos, int ypos, GameManager* managerRef);

	void Update() override;
	void PhysicsUpdate() override;
	void OnCollision(GameObject* col) override;
	void SetProperties() override;
	void SetOBJDimension(int height, int width) override
	{
		OBJHeight = height;
		OBJWidth = width;
	}
	void Hit() override;
	void RemoveBrick();
	bool CanBeRemoved(GameObject* obj) const override
	{
		return obj->IsDestroyed && obj->GetTag() == T_BRICK;
	}

	int ID = 0;

private:
	GameManager* manager;

	Mix_Chunk* brickBreak_SFX;
};