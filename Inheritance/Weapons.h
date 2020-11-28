#pragma once

#include <string>
#include "Attributes.h"
#include "Dice.h"

class Weapon
{
public:
	Weapon(const std::string& name, int rank);
	virtual ~Weapon() = default;

	const std::string& GetName() const;
	int GetRank() const;
	virtual int CalculateDamage(const Attributes& attr, Dice& dice) const = 0;

private:
	std::string mName;
	int mRank;
};

class Fists : public Weapon
{
public:
	Fists();
	int CalculateDamage(const Attributes& attr, Dice& dice) const override;
};

class Knife : public Weapon
{
public:
	Knife();
	int CalculateDamage(const Attributes& attr, Dice& dice) const override;
};

class Bat : public Weapon
{
public:
	Bat();
	int CalculateDamage(const Attributes& attr, Dice& dice) const override;
};
