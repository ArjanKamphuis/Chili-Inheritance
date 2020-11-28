#include "Fighters.h"

#include <cassert>
#include <iostream>

MemeFighter::~MemeFighter()
{
	delete mWeapon;
	mWeapon = nullptr;
}

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

void MemeFighter::Attack(MemeFighter& other) const
{
	if (IsAlive() && other.IsAlive())
	{
		assert(mWeapon);
		std::cout << mName << " attacks " << other.mName << " with his " << mWeapon->GetName() << "!" << std::endl;
		ApplyDamageTo(other, mWeapon->CalculateDamage(mAttributes, mDice));
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

void MemeFighter::GiveWeapon(Weapon* pNewWeapon)
{
	delete mWeapon;
	mWeapon = pNewWeapon;
}

Weapon* MemeFighter::PilferWeapon()
{
	Weapon* pWeapon = mWeapon;
	mWeapon = nullptr;
	return pWeapon;
}

MemeFighter::MemeFighter(const std::string& name, int hp, int speed, int power, Weapon* pWeapon)
	: mName(name), mAttributes({ hp, speed, power}), mWeapon(pWeapon)
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

MemeStoner::MemeStoner(const std::string& name, Weapon* pWeapon)
	: MemeFighter(name, 80, 4, 10, pWeapon)
{}

void MemeStoner::SpecialMove(MemeFighter&)
{
	if (IsAlive())
	{
		if (Roll() > 3)
		{
			std::cout << mName << " smokes the dank sticky icky, becoming Super " << mName << std::endl;
			mName = "Super " + mName;
			mAttributes.Speed += 3;
			mAttributes.Power = (mAttributes.Power * 69) / 42;
			mAttributes.Hp += 10;
		}
		else
			std::cout << mName << " spaces out." << std::endl;
	}
}

MemeFrog::MemeFrog(const std::string& name, Weapon* pWeapon)
	: MemeFighter(name, 69, 7, 14, pWeapon)
{}

void MemeFrog::SpecialMove(MemeFighter& other)
{
	if (IsAlive() && other.IsAlive())
	{
		if (Roll() > 4)
		{
			std::cout << mName << " attacks " << other.GetName() << " with a rainbow beam!" << std::endl;
			ApplyDamageTo(other, Roll(3) + 20);
		}
		else
			std::cout << mName << " falls off his unicycle." << std::endl;
	}
}

void MemeFrog::Tick()
{
	if (IsAlive())
	{
		std::cout << mName << " is hurt by the bad AIDS!" << std::endl;
		ApplyDamageTo(*this, Roll());
		MemeFighter::Tick();
	}
}
