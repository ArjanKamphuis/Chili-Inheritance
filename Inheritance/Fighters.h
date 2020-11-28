#pragma once

#include <string>
#include "Attributes.h"
#include "Dice.h"
#include "Weapons.h"

class MemeFighter
{
public:
	virtual ~MemeFighter();

	const std::string& GetName() const;
	int GetInitiative() const;
	bool IsAlive() const;

	void Attack(MemeFighter& other) const;
	virtual void SpecialMove(MemeFighter&) = 0;
	virtual void Tick();

	void GiveWeapon(Weapon* pNewWeapon);
	Weapon* PilferWeapon();
	bool HasWeapon() const;
	const Weapon& GetWeapon() const;

protected:
	MemeFighter(const std::string& name, int hp, int speed, int power, Weapon* pWeapon = nullptr);
	void ApplyDamageTo(MemeFighter& target, int damage) const;
	int Roll(int nDice = 1) const;

protected:
	Attributes mAttributes;
	std::string mName;

private:
	Weapon* mWeapon = nullptr;
	mutable Dice mDice;
};

class MemeStoner : public MemeFighter
{
public:
	MemeStoner(const std::string& name, Weapon* pWeapon = nullptr);
	void SpecialMove(MemeFighter&) override;
};

class MemeFrog : public MemeFighter
{
public:
	MemeFrog(const std::string& name, Weapon* pWeapon = nullptr);
	void SpecialMove(MemeFighter& other) override;
	void Tick() override;
};
