#include "CollisionManager.h"
#include <iostream>
#include "../GAME/GAMEINFO.h"
#include "../GAME/GameObject.h"

CollisionManager::CollisionManager()
{
}

void CollisionManager::OnCollided()
{
}

#pragma region  Checking Collision & Properties
bool CollisionManager::CheckCollision(SDL_Rect objA, SDL_Rect objB, SDL_Rect* rect)
{
	XCollision = false;
	YCollision = false;

	ColPoints a(objA);
	ColPoints b(objB);

    //if (!CheckSweptCollision(a, b, TIME_STEP)) return false;
	if (!OnCollisionExit(a, b)) return false;
	if (OnCollisionEnter(a, b))
		return true;
}

bool CollisionManager::CheckCollisionProperties(GameObject* _object, SDL_Rect rect)
{
	if (GetME() == _object->GetCollider().GetME())
		return false;

	if (!CheckCollision(GetCollisionRect(), _object->GetCollider().GetCollisionRect(), &rect))
		return false;

	if (_object->IsDestroyed) return false;

	return true;
}
#pragma endregion

#pragma region Enter & Exit
bool CollisionManager::OnCollisionEnter(ColPoints a, ColPoints b)
{
	if (!ONCOLLISIONEXIT) return false;

	bool checkXCol = (a.right > b.left && a.left < b.right);
	bool checkYCol = (a.bottom > b.top && a.top < b.bottom);

	if (checkXCol && checkYCol) {

		overlapX = std::max(0.0f, std::min(a.right, b.right) - std::max(a.left, b.left));
		overlapY = std::max(0.0f, std::min(a.bottom, b.bottom) - std::max(a.top, b.top));

		const float tolerance = 015.f; // 1

		if (std::abs(overlapX - overlapY) <= tolerance) {
			// Overlaps are within tolerance
			XCollision = true;
			YCollision = true;
		}
		else if (overlapX > overlapY + tolerance) {
			// X overlap is much larger
			XCollision = true;
			YCollision = false;
		}
		else if (overlapY > overlapX + tolerance) {
			// Y overlap is much larger
			XCollision = false;
			YCollision = true;
		}

		ONCOLLISIONEXIT = false;
		return true;
	}

	return false;
}
bool CollisionManager::OnCollisionExit(ColPoints a, ColPoints b)
{
	bool checkXCol = (a.right < b.left || a.left > b.right);
	bool checkYCol = (a.bottom < b.top || a.top > b.bottom);

	if (checkXCol || checkYCol)
	{
		XCollision = !checkXCol;
		YCollision = !checkYCol;
		ONCOLLISIONEXIT = true;
		return false;
	}
	return true;
}
#pragma endregion

#pragma region  Set Collision Position
void CollisionManager::SetCollisionMovementDirection(SDL_Rect position)
{
	CollisionRect = position;
}

void CollisionManager::UpdateCollisionForRotation(SDL_Rect& collisionRect, int rotationAngle)
{
	SDL_Rect rect;

	rect.x = collisionRect.x;
	rect.y = collisionRect.y - collisionRect.w;
	rect.w = collisionRect.h;
	rect.h = collisionRect.w;

	SetCollisionRect(rect);
}
#pragma endregion