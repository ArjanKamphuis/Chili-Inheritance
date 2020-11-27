#include "MemeFrog.h"

#include <iostream>

MemeFrog::MemeFrog(const std::string& name)
	: MemeFighter(name, 69, 7, 14)
{}

void MemeFrog::SpecialMove(MemeFighter & other)
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
