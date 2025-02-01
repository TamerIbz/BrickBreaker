#include "Player.h"
#include "../Manager/GameManager.h"


Player::Player(GameManager* managerRef) : manager(managerRef)
{
	SetProperties();
	SetOBJDimension(20, 100);// 20  // 100 // 

	//x,y,w,h
	OBJRect = {
		(WIDTH - this->OBJWidth) / 2,
		HEIGHT - 65, // 135
		this->OBJWidth,
		this->OBJHeight };

	GetCollider().SetCollisionRect(OBJRect);
	SetStartingPoint(OBJRect);
}
 
void Player::SetProperties()
{
	SetPath("Assets/Player/Player2.png");
	SetTag(T_PLAYER);
}

void Player::Hit()
{
}

//void Player::RemoveFromRegistry(bool _break)
//{
//}

#pragma region Movement
void Player::Movement()
{

	switch (MovementDirection)
	{
	case NONE:
		break;
	case Left:
		if (OBJRect.x > 0)
			Move(-1);
		break;
	case Right:
		if ((OBJRect.x + OBJWidth) < WIDTH)
			Move(1);
		break;
	//case Up:
	//	OBJRect.y += -1 * (int)movementSpeed;
	//	collider.SetCollisionMovementDirection(OBJRect);
	//	break;
	//case Down:
	//	OBJRect.y += 1 * (int)movementSpeed;
	//	collider.SetCollisionMovementDirection(OBJRect);
	//	break;
	}
}

void Player::Move(int direction)
{
	OBJRect.x += direction * (int)movementSpeed * TIME_STEP;
	GetCollider().SetCollisionMovementDirection(OBJRect);
}

void Player::MoveCollided(int overlapDirection)
{
	OBJRect.x += overlapDirection;
	GetCollider().SetCollisionMovementDirection(OBJRect);
}

float Player::GetOverlapDirection(SDL_Rect objA, SDL_Rect objB)
{
	return (objA.x + objA.w) - objB.x;
}

void Player::ChangeMovementDirection(PlayerMovementDirection direction)
{
	MovementDirection = direction;
}
#pragma endregion

void Player::Update()
{

	if (!GAMEPLAYING) return;
	Movement();

	if (POSITION::CHECK_OFFSCREEN_POSITION(GetRect()))
		ResetToStartingPoint();
}

void Player::PhysicsUpdate()
{
	for (auto& colliderObjs : GameObject::getRegistry())
		OnCollision(colliderObjs->GetME());
}

#pragma region Collision
void Player::OnCollision(GameObject* _object)
{
	if (GetCollider().CheckCollisionProperties(_object, GetRect()))
	{
#pragma region Y Collision
		if (GetCollider().YCollision)
		{
			if (_object->GetTag() == T_BARRIER && _object->GetTag() != T_BALL)
			{
				SDL_Rect colRect = _object->GetCollider().GetCollisionRect();
				OBJRect.x = colRect.x + colRect.w;

				if (GetOverlapDirection(colRect, OBJRect) < OBJRect.x) //Left Barrier -> Move Right
					MoveCollided(GetOverlapDirection(colRect, OBJRect));
				if (OBJRect.x > GetOverlapDirection(OBJRect, colRect)) // Right Barrier -> Move Left
					MoveCollided(-GetOverlapDirection(OBJRect, colRect));
			}
		}

#pragma endregion

		//	// temp -> can remove after -> keep if 
		//	if (collider.XCollision)
		//	{
		//		//if (SDL_HasIntersection(&OBJRect, &col->GetRect()) && OBJRect.y < col->GetRect().y) { // bottom
		//		//	float overlapX = (OBJRect.y + OBJRect.h) - col->GetRect().y;
		//		//	OBJRect.y -= overlapX;  
		//		//	collider.SetCollisionMovementDirection(OBJRect);
		//		//}

		//		//if (SDL_HasIntersection(&OBJRect, &col->GetRect()) && OBJRect.y > col->GetRect().y) { // top
		//		//	float overlapX = col->GetRect().y + col->GetRect().h - OBJRect.y;
		//		//	OBJRect.y += overlapX;
		//		//	collider.SetCollisionMovementDirection(OBJRect);
		//		//}
		//	}
		//}
	}
	if (GetRect().x + OBJWidth >= WIDTH)
		Move(-1);
	else if (GetRect().x <= 0)
		Move(1);
}
#pragma endregion
