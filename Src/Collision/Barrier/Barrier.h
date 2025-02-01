#pragma once
#include "../../GAME/GameObject.h"

class GameManager;

class Barrier : public GameObject
{
public:
	Barrier();
	Barrier(int xPos, int YPos, int width, int height, bool Rotate, int Degrees, GameManager* managerRef);

	void Update() override;
	void PhysicsUpdate() override;
	void OnCollision(GameObject* col) override;
	void SetProperties() override;
	void Hit() override;

	bool CanBeRemoved(GameObject* obj) const override
	{
		return true;
	}

	void SetOBJDimension(int height, int width) override
	{
		OBJHeight = height;
		OBJWidth = width;
	}

public:
	int BarrierX;
	int BarrierY; 

	int orgObjHeight;
	int orgObjWidth = 15;

	bool orgRotate = false;
	int orgDegrees = 0;

private:
	GameManager* manager;
};