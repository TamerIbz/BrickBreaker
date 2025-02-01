#include "Brick.h"

Brick::Brick(int xpos, int ypos, GameManager* managerRef) : manager(managerRef)
{
	SetProperties();

	OBJRect = { xpos,
		ypos,
		this->OBJWidth,
		this->OBJHeight };

	GetCollider().SetCollisionRect(OBJRect);
}

void Brick::SetProperties()
{
	SetOBJDimension(40, 40);
	SetPath("Assets/Brick/Purple_B.png");
	SetTag(T_BRICK);

	AudioManager::getInstance().LoadSFX(brickBreak_SFX, "Assets/Audio/SFX/Hitting/Ball-Break-Brick.wav");

	GetLives().AddLives(0);
}

#pragma region Hit & Die
void Brick::Hit()
{
	if (RemoveANDCheckDeath())
		RemoveBrick(); // dead and hit
	else
	{
		switch (GetLives().GetLives())
		{
		case 3: SetPath("Assets/Brick/Grey_B.png"); break;
		case 2: SetPath("Assets/Brick/Blue_B.png"); break;
		case 1: SetPath("Assets/Brick/Yellow_B.png"); break;
		}
		// not dead but hit
	}
}

void Brick::RemoveBrick()
{
	AudioManager::getInstance().PlaySFX(brickBreak_SFX, 0);

	RemoveFromRegistry(true);
	manager->level->RemoveBricks(ID);
	return;
}
#pragma endregion

#pragma region Physics
void Brick::Update()
{
}

void Brick::PhysicsUpdate()
{
	for (const auto& colliderObjs : GameObject::getRegistry())
		OnCollision(colliderObjs->GetME());
}

void Brick::OnCollision(GameObject* _object)
{
	if (GetCollider().CheckCollisionProperties(_object, GetRect()))
	{
	}
}
#pragma endregion