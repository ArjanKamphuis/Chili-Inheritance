#pragma once

#include <string>
#include "Attributes.h"
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
	const Attributes& GetAttributes() const;

protected:
	MemeFighter(const std::string& name, int hp, int speed, int power);
	void ApplyDamageTo(MemeFighter& target, int damage) const;
	int Roll(int nDice = 1) const;

protected:
	Attributes mAttributes;
	std::string mName;

private:
	mutable Dice mDice;
};

