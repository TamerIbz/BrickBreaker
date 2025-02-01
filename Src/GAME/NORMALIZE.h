#pragma once
#include <cmath>

static class NORMALIZE
{
public:
	static void Normalize(float& x, float& y) {
		float length = sqrt(x * x + y * y);
		if (length != 0) {
			x /= length;
			y /= length;
		}
	}
};
