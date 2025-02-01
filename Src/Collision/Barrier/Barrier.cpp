#include "Barrier.h"
#include "../../Manager/GameManager.h"

Barrier::Barrier()
{
	SetProperties();
}

Barrier::Barrier(int xPos, int YPos, int width, int height, bool Rotate, int Degrees, GameManager* managerRef) :
	BarrierX(xPos), BarrierY(YPos), orgObjWidth(width), orgObjHeight(height), orgRotate(Rotate), orgDegrees(Degrees), manager(managerRef)
{
	SetProperties();
}

void Barrier::SetProperties()
{
	SetPath("Assets/Barrier/Barrier.png");
	SetTag(T_BARRIER);

	SetOBJDimension(orgObjHeight, orgObjWidth);

	OBJRect = {
	BarrierX,
	BarrierY,
	OBJWidth,
	OBJHeight };

	Rotate = orgRotate;
	Degrees = orgDegrees;


	if (Rotate)
		GetCollider().UpdateCollisionForRotation(OBJRect, Degrees);
	else
		GetCollider().SetCollisionRect(OBJRect);
}

void Barrier::Hit()
{
}

#pragma region Physics
void Barrier::Update()
{
}

void Barrier::PhysicsUpdate()
{
	for (const auto& colliderObjs : GameObject::getRegistry())
		OnCollision(colliderObjs->GetME());
}

void Barrier::OnCollision(GameObject* _object)
{
	if (_object->GetTag() == T_BARRIER) return;
	if (GetCollider().CheckCollisionProperties(_object, GetCollider().GetCollisionRect()))
	{
		// empty but need this so we can access on col exit & enter
	}
}
#pragma endregion