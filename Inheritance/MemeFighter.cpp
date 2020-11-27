#include "MemeFighter.h"

#include <iostream>

const std::string& MemeFighter::GetName() const
{
	return mName;
}

int MemeFighter::GetInitiative() const
{
	return mSpeed + Roll(2);
}

bool MemeFighter::IsAlive() const
{
	return mHp > 0;
}

void MemeFighter::Punch(MemeFighter& other)
{
	if (IsAlive() && other.IsAlive())
	{
		std::cout << mName << " punches " << other.mName << "!" << std::endl;
		ApplyDamageTo(other, mPower + Roll(2));
	}
}

void MemeFighter::Tick()
{
	if (IsAlive())
	{
		const int recovery = Roll();
		std::cout << mName << " recovers " << recovery << " HP." << std::endl;
		mHp += recovery;
	}
}

MemeFighter::MemeFighter(const std::string& name, int hp, int speed, int power)
	: mName(name), mHp(hp), mSpeed(speed), mPower(power)
{
	std::cout << name << " enters the ring!" << std::endl;
}

void MemeFighter::ApplyDamageTo(MemeFighter& target, int damage) const
{
	target.mHp -= damage;
	std::cout << target.mName << " takes " << damage << " damage." << std::endl;
	if (!target.IsAlive())
		std::cout << "As the life leaves " << target.mName << "'s body, so does the poop." << std::endl;
}

int MemeFighter::Roll(int nDice) const
{
	return mDice.Roll(nDice);
}
