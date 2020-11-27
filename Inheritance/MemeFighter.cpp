#include "MemeFighter.h"

#include <iostream>

const std::string& MemeFighter::GetName() const
{
	return mName;
}

int MemeFighter::GetInitiative() const
{
	return mAttributes.Speed + Roll(2);
}

bool MemeFighter::IsAlive() const
{
	return mAttributes.Hp > 0;
}

void MemeFighter::Punch(MemeFighter& other)
{
	if (IsAlive() && other.IsAlive())
	{
		std::cout << mName << " punches " << other.mName << "!" << std::endl;
		ApplyDamageTo(other, mAttributes.Power + Roll(2));
	}
}

void MemeFighter::Tick()
{
	if (IsAlive())
	{
		const int recovery = Roll();
		std::cout << mName << " recovers " << recovery << " HP." << std::endl;
		mAttributes.Hp += recovery;
	}
}

const Attributes& MemeFighter::GetAttributes() const
{
	return mAttributes;
}

MemeFighter::MemeFighter(const std::string& name, int hp, int speed, int power)
	: mName(name), mAttributes({ hp, speed, power})
{
	std::cout << name << " enters the ring!" << std::endl;
}

void MemeFighter::ApplyDamageTo(MemeFighter& target, int damage) const
{
	target.mAttributes.Hp -= damage;
	std::cout << target.mName << " takes " << damage << " damage." << std::endl;
	if (!target.IsAlive())
		std::cout << "As the life leaves " << target.mName << "'s body, so does the poop." << std::endl;
}

int MemeFighter::Roll(int nDice) const
{
	return mDice.Roll(nDice);
}
