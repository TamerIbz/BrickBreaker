#pragma once
#include <iostream>
#include <string>

class ScoreManager
{
public:
#pragma region GetScore
	const int& GetScoreValue() { return score; }
	const std::string& GetScoreText() { return score_text; }
	const std::string& GetHighscoreText() { return highscore_text; }
#pragma endregion

#pragma region  SetScore
	void AddScore(int amount)
	{
		score += amount;
		SetValueToScoreText();
	}

	void MultiplyScore(float multiplier)
	{
		score *= multiplier;
		SetValueToScoreText();
	}

	void SetScoreValue(int _value)
	{ 
		score = _value;
		SetValueToScoreText();
	}
#pragma endregion

#pragma region SetHighscore
	void SetHighscore()
	{
		if (score > highscore)
			highscore = score;

		SetValueToHighscoreText();
	}
#pragma endregion

public:
	ScoreManager()
	{
		SetScoreValue(0);
	}

private:
	unsigned int score = 0;
	std::string score_text;

	unsigned int highscore = 0;
	std::string highscore_text = " ";

	void SetValueToScoreText() { score_text = std::to_string(score); }
	void SetValueToHighscoreText() { highscore_text = "Highscore: " + std::to_string(highscore); }
};