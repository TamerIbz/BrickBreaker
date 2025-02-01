#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_surface.h"
#include "SDL_mixer.h"
#include <iostream>
#include <vector>
#include "../GAME/STREAK.h"
#include "../GAME/GAMEINFO.h"
#include "../GAME/POSITION.h"
#include "../GAME/RANDOM.h"
#include "../GAME/NORMALIZE.h"
#include "../GAME/MATH.h"
#include "../GAME/TIMER/Timer.h"
#include "../FPS/FrameRate.h"
#include "../Collision/CollisionManager.h"
#include "../Audio/AudioManager.h"
#include "../Live/LiveManager.h"
#include "../Tag/TagManager.h"
#include "../GAME/MENU_STATES.h"
#include "../GAME/GAME_STATES.h"

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
class FrameRate;
class CollisionManager;

class GameObject
{
public:
	virtual ~GameObject() = default;

	static std::vector<GameObject*>& getRegistry() {
		static std::vector<GameObject*> registry;
		return registry;
	}


	GameObject() : OBJHeight(0), OBJWidth(0){
		getRegistry().push_back(this); // Register this instance
	}

	virtual void SetProperties() = 0;
	virtual void Update() = 0;
	virtual void PhysicsUpdate() = 0;
	virtual void SetOBJDimension(int height, int width) = 0;
	void RemoveFromRegistry(bool _break)
	{
		for (auto it = getRegistry().begin(); it != getRegistry().end();)
		{
			GameObject* thing = *it;

			if (!CanBeRemoved(thing))
			{
				++it; // Move to the next element if no erasure happens
				continue;
			}
		
			it = getRegistry().erase(it); // Erase and get the next valid iterator
			if (_break)
				break;
		}
	}
	virtual bool CanBeRemoved(GameObject* obj) const { return false; }
	virtual void OnCollision(GameObject* col) = 0;
	virtual void Hit() = 0;
	bool RemoveANDCheckDeath()
	{
		live.RemoveLives(1);

		if (live.CheckDeathAmount())
		{
			IsDestroyed = true;
			collider.SetCollisionRect(emptyR); 

			return true;
		}
		else
			return false;
	}

	bool CheckDeath()
	{
		return live.CheckDeathAmount();
	}

	bool Rotate = false;
	int Degrees = 0;

	bool IsDestroyed = false;
	SDL_Rect emptyR = { 0,0,0,0 };

	// get rect
	SDL_Rect& GetRect() { return OBJRect; }

	// set starting point
	void SetStartingPoint(SDL_Rect rect) { 
		StartingPoint.x = rect.x, StartingPoint.y = rect.y; }
	// reset position to starting position
	void ResetToStartingPoint(){
		POSITION::RESET_POSITION(GetRect(), StartingPoint);
		collider.SetCollisionRect(GetRect());
	}
	// get & set path
	const char* GetPath() const {return imgPath.c_str(); }
	void SetPath(const char* newPath) {imgPath = newPath;  }
	// get img
	SDL_Surface* GetImage() { return image; }
	//set tag
	void SetTag(const char* newTag) { tag = newTag; }
	//get tag
	const char* GetTag() { return tag; }

	GameObject* GetME() { return this; }
	CollisionManager& GetCollider() { return collider; } // collision
	LiveManager& GetLives() { return live; } // health / lives

protected:
	 int OBJHeight;
	 int OBJWidth;
	 SDL_Rect OBJRect = { 0,0,0,0 };
	 SDL_Point StartingPoint;

private:
	 CollisionManager collider;
	 LiveManager live;

private:
	std::string imgPath;
	SDL_Surface* image;
	const char* tag;
};
#endif