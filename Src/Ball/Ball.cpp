#include "Ball.h"
#include "../Manager/GameManager.h"

bool ONSTREAK = false;

Timer replayTimer(.65); 

#pragma region  Properties
Ball::Ball(GameManager* managerRef) : manager(managerRef)
{
	SetOBJDimension(20, 20);
	SetProperties();
	//(HEIGHT - OBJHeight) / 2,
	//(WIDTH - OBJWidth) / 2
	OBJRect = { (WIDTH - OBJWidth) / 2,
			initialYPos,
				OBJWidth,
				OBJHeight };

	GetCollider().SetCollisionRect(OBJRect);
	SetStartingPoint(OBJRect);

	SetInitialMov();
}

void Ball::SetProperties()
{
	SetPath("Assets/Ball/Ball.png");
	SetTag(T_BALL);

	AudioManager::getInstance().LoadSFX(hit_SFX,"Assets/Audio/SFX/Hitting/Ball-Hit.wav");
	AudioManager::getInstance().LoadSFX(start_SFX, "Assets/Audio/SFX/GAME/GameStart.wav");
	AudioManager::getInstance().LoadSFX(die_SFX, "Assets/Audio/SFX/Die/Ball-Die.wav");

	GetLives().AddLives(3); // 3
	CurrentXPositionChecker.resize(2);
	CurrentYPositionChecker.resize(2);
}

void Ball::SetInitialMov() 	// Random movement position
{
	unsigned seed = time(0);
	srand(seed);

	float angle = Random::RANDOMISE(30, 150) * (M_PI / 180.0f);// between 30 and 150 deg
	int randX = Random::RANDOMISE(0, 1);
	velocityX = randX == 0 ? -initialMovSpeed * cos(angle) : initialMovSpeed * cos(angle); // Move left or right
	velocityY = -initialMovSpeed * sin(angle); // Move upwards
}
#pragma endregion

#pragma region Phyiscs & Ball Bouncing
void Ball::Update()
{
	if (!GAMEPLAYING) return;
	replayTimer.SetTimerCountdown();

	if (replayTimer.IsCounting()) return;

	if (!initialCollision)
	{
		const float MAX_BALL_VELOCITY = 400.0f;  // Maximum velocity limit
		velocityX = std::min(velocityX, MAX_BALL_VELOCITY);
		velocityY = std::min(velocityY, MAX_BALL_VELOCITY);
		OBJRect.x += velocityX * TIME_STEP;
		OBJRect.y += velocityY * TIME_STEP;

		if (POSITION::CHECK_OFFSCREEN_POSITION(GetRect()))
		{
			if (DeathPosCheck()) // DEATH -> below player
			{
				Hit();
				replayTimer.SetTimer([this]() {
					OnFinishTimer();
					});
				manager->level->player->ResetToStartingPoint();
			}

			ResetToStartingPoint();
			SetInitialMov();
		}
		GetCollider().SetCollisionRect(OBJRect);
	}
}

void Ball::PhysicsUpdate()
{
	for (const auto& colliderObjs : GameObject::getRegistry())
		OnCollision(colliderObjs->GetME());
}

void Ball::ReflectBounce(float& velocityX, float& velocityY, float normalX, float normalY)
{
	NORMALIZE::Normalize(normalX, normalY);
	float dot = MATH::DOT(velocityX, velocityY, normalX, normalY);
	velocityX -= 2 * dot * normalX;
	velocityY -= 2 * dot * normalY;
}

void Ball::Bounce(GameObject* col)
{
	float normalX = 0.f, normalY = 0.f;

	if (GetCollider().XCollision && GetCollider().YCollision)
	{
		normalX = (velocityX > 0) ? 1.0f : -1.0f;
		normalY = (velocityY > 0) ? 1.0f : -1.0f;

		if (velocityX == 0)
			velocityX = -initialMovSpeed;
		if (velocityY == 0)
			velocityY = -initialMovSpeed;
	}
	else if (GetCollider().XCollision)
	{ // Reflect horizontally
		normalX = 0.f;
		normalY = (velocityY > 0) ? 1.0f : -1.0f;

		if (velocityY == 0)
			velocityY = -initialMovSpeed;

	}
	else if (GetCollider().YCollision)
	{ // Reflect vertically
		normalX = (velocityX > 0) ? 1.0f : -1.0f;
		normalY = 0.f;

		if (velocityX == 0)
			velocityX = -initialMovSpeed;

	}
	ReflectBounce(velocityX, velocityY, normalX, normalY);
}

void Ball::OnCollision(GameObject* _object)
{
	if (GetCollider().CheckCollisionProperties(_object, GetCollider().GetCollisionRect())) // getrect()
	{
		if (_object->GetTag() == T_BARRIER ||
			_object->GetTag() == T_PLAYER ||
			_object->GetTag() == T_BRICK)
		{
			if (!_object->GetCollider().ONCOLLISIONEXIT) return;
			Bounce(_object);
			HittingObjects(_object);
		}
	}
}

void Ball::HittingObjects(GameObject* _object)
{
	if (_object->GetTag() == T_BRICK) // hit bricks
	{
		if (!ONSTREAK)
		{
			manager->Score.AddScore(NONSTREAKINCREASEVALUE);
			ONSTREAK = !ONSTREAK;// hit brick -> start streak
		}
		else
			manager->Score.MultiplyScore(STREAKMULTIPLIER);

		_object->Hit(); 
	}
	else if (_object->GetTag() == T_PLAYER)
		if (ONSTREAK) ONSTREAK = !ONSTREAK;// hit player -> cancel streak

	CheckPositionNOTSame(_object);
	AudioManager::getInstance().PlaySFX(hit_SFX, 0);

}

void Ball::Hit()
{
	if (ONSTREAK) ONSTREAK = !ONSTREAK;// die -> cancel streak
	if (RemoveANDCheckDeath()) // death
		manager->GameOver(GAME_STATES::LOSE);
	else
		AudioManager::getInstance().PlaySFX(die_SFX, 0); // only want to play when its not gameover
}
#pragma endregion

#pragma region Checking position is not the same & Random ball position randomly

void Ball::CheckPositionNOTSame(GameObject* _object)
{
	SetPositionChecker(CurrentXPositionChecker, currentXPositionCheckerIndex, GetRect().x);
	SetPositionChecker(CurrentYPositionChecker, currentYPositionCheckerIndex, GetRect().y);

	// X
	if (_object->GetTag() == T_PLAYER)
	{
		if (CurrentXPositionChecker[0] == CurrentXPositionChecker[1])
			SetInitialMov();
		else
			RandomiseRandomPositionRandomly();
	}

	// Y
	if (CurrentYPositionChecker[0] == CurrentYPositionChecker[1])
		SetInitialMov();

	AddANDCheckPositionIndex(currentXPositionCheckerIndex);
	AddANDCheckPositionIndex(currentYPositionCheckerIndex);
}

void Ball::AddANDCheckPositionIndex(int& index)
{
	index++;
	if (index > 1)
		index = 0;
}

void Ball::SetPositionChecker(std::vector<int>& pos, int& checkerIndex, int axis)
{
	if (checkerIndex == 0)
		pos[0] = axis;
	else if (checkerIndex == 1)
		pos[1] = axis;
}

void Ball::RandomiseRandomPositionRandomly() // Randomly randomise position so game because unpredictable and more fun
{
	int rand = Random::RANDOMISE(0, 11);
	if (rand <= 3)
		SetInitialMov();
}
#pragma endregion

#pragma region End Timer
void Ball::OnFinishTimer()
{
	if (!CheckDeath())
		AudioManager::getInstance().PlaySFX(start_SFX, 0);
}
#pragma endregion
