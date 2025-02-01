#pragma once
#include <iostream>
#include "SDL.h"
#include <vector>

#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H
class GameObject;

struct ColPoints
{
	float left;
	float right;
	float top;
	float bottom;

	SDL_Rect objRect;

	ColPoints(SDL_Rect& rect) {
		left = rect.x;
		right = rect.x + rect.w;
		top = rect.y;
		bottom = rect.y + rect.h;

		objRect = rect;
	}
};

class CollisionManager
{
public:
	CollisionManager();
	CollisionManager* GetME() { return this; }

#pragma region  Get & Set Rect
	void SetCollisionRect(SDL_Rect& rect)
	{
		CollisionRect = rect;
	}
	SDL_Rect& GetCollisionRect()
	{
		return CollisionRect;
	}
	void UpdateCollisionForRotation(SDL_Rect& collisionRect, int rotationAngle);
#pragma endregion
	void OnCollided();
	bool CheckCollision(SDL_Rect objA, SDL_Rect objB, SDL_Rect* rect);
	bool CheckCollisionProperties(GameObject* _object, SDL_Rect rect);
	void SetCollisionMovementDirection(SDL_Rect position);
	bool OnCollisionEnter(ColPoints a, ColPoints b);
	bool OnCollisionExit(ColPoints a, ColPoints b);

	void ResetCollision()
	{
		ONCOLLISIONEXIT = false;
		XCollision = false;
		YCollision = false;
	}

public:
	float overlapX;
	float overlapY;

	bool XCollision = false;
	bool YCollision = false;
	bool ONCOLLISIONEXIT = false; // this may not work (= false), if go doesnt have col code
private:
	SDL_Rect CollisionRect;
};

#endif