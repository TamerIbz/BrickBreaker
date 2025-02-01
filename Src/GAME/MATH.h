#pragma once

struct MATH
{
public:
	static float DOT(float& velocityX, float& velocityY, float normalX, float normalY)
	{
		return velocityX * normalX + velocityY * normalY;
	}

	static float CROSS(const SDL_Point& a, const SDL_Point& b) {
		return a.x * b.y - a.y * b.x;
	}
};