#pragma once
#include <iostream>
#include <string>

class LiveManager
{
public:
	const int& GetLives() { return lives; }
	std::string& GetLiveText() { return live_text; }

#pragma region  Add & Remove Lives
	void AddLives(int amount)
	{
		lives += amount;
		SetValueToLiveText();
	}

	void RemoveLives(int amount)
	{
		lives -= amount;
		SetValueToLiveText();
	}

	bool CheckDeathAmount()
	{
		return lives <= 0;
	}
#pragma endregion

private:
	int lives = 0;
	std::string live_text = " ";

	void SetValueToLiveText() { live_text = std::to_string(lives); }
};