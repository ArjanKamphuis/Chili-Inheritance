#include "MemeStoner.h"

#include <iostream>

MemeStoner::MemeStoner(const std::string& name)
	: MemeFighter(name, 80, 4, 10)
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
