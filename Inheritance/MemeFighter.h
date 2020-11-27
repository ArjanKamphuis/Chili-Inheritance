#pragma once

#include <string>
#include "Dice.h"

class MemeFighter
{
public:
	const std::string& GetName() const;
	int GetInitiative() const;
	bool IsAlive() const;
	void Punch(MemeFighter& other);
	virtual void SpecialMove(MemeFighter&) = 0;
	virtual void Tick();
	virtual ~MemeFighter() = default;

protected:
	MemeFighter(const std::string& name, int hp, int speed, int power);
	void ApplyDamageTo(MemeFighter& target, int damage) const;
	int Roll(int nDice = 1) const;

protected:
	int mHp;
	int mSpeed;
	int mPower;
	std::string mName;

private:
	mutable Dice mDice;
};

