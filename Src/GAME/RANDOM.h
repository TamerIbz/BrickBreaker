#pragma once

#include <ctime>
#include <random>

#ifndef RANDOM
#define RANDOM
class Random
{
public:
	template <typename T>
	static auto RANDOMISE(T min, T max)
	{
		std::random_device rd; 
		std::mt19937 eng(rd()); 
		std::uniform_int_distribution<> distr(min, max); // range
		return distr(eng);
	}
};
#endif