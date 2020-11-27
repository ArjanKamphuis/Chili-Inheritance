#pragma once

#include <random>

class Dice
{
public:
	int Roll(int nDice);

private:
	std::uniform_int_distribution<int> mD6 = std::uniform_int_distribution<int>(1, 6);
	std::mt19937 mRng = std::mt19937(std::random_device{}());
};
