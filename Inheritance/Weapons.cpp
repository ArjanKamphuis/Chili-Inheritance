#include "Weapons.h"

Weapon::Weapon(const std::string& name, int rank)
	: mName(name), mRank(rank)
{
}

const std::string& Weapon::GetName() const
{
	return mName;
}

int Weapon::GetRank() const
{
	return mRank;
}

Fists::Fists()
	: Weapon("fists", 0)
{
}

int Fists::CalculateDamage(const Attributes& attr, Dice& dice) const
{
	return attr.Power + dice.Roll(2);
}

Knife::Knife()
	: Weapon("knife", 2)
{
}

int Knife::CalculateDamage(const Attributes& attr, Dice& dice) const
{
	return attr.Speed * 3 + dice.Roll(3);
}

Bat::Bat()
	: Weapon("bat", 1)
{
}

int Bat::CalculateDamage(const Attributes& attr, Dice& dice) const
{
	return attr.Power * 2 + dice.Roll(1);
}
