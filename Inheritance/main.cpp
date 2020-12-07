#include <algorithm>
#include <conio.h>
#include <iostream>
#include <typeinfo>

#include "Fighters.h"
#include "Weapons.h"

#ifdef _DEBUG
#include <crtdbg.h>
#endif

void TakeWeaponIfDead(MemeFighter& taker, MemeFighter& giver)
{
	if (taker.IsAlive() && !giver.IsAlive() && giver.HasWeapon()
		&& (giver.GetWeapon().GetRank() > taker.GetWeapon().GetRank()))
	{
		std::cout << taker.GetName() << " takes the " << giver.GetWeapon().GetName() << " from " << giver.GetName() << "'s still-cooling corpse." << std::endl;
		taker.GiveWeapon(giver.PilferWeapon());
	}
}

void Engage(MemeFighter& f1, MemeFighter& f2)
{
	MemeFighter* p1 = &f1;
	MemeFighter* p2 = &f2;

	if (p1->GetInitiative() < p2->GetInitiative())
		std::swap(p1, p2);

	p1->Attack(*p2);
	TakeWeaponIfDead(*p1, *p2);
	p2->Attack(*p1);
	TakeWeaponIfDead(*p2, *p1);
}

void DoSpecials(MemeFighter& f1, MemeFighter& f2)
{
	MemeFighter* p1 = &f1;
	MemeFighter* p2 = &f2;

	if (p1->GetInitiative() < p2->GetInitiative())
		std::swap(p1, p2);

	p1->SpecialMove(*p2);
	TakeWeaponIfDead(*p1, *p2);
	p2->SpecialMove(*p1);
	TakeWeaponIfDead(*p2, *p1);
}

bool AreSameType(MemeFighter& f1, MemeFighter& f2)
{
	return (typeid(f1) == typeid(f2));
}

template<typename T, class P>
void shuffle_partition(std::vector<T>& vec, const P& pred)
{
	std::random_shuffle(vec.begin(), vec.end());
	std::partition(vec.begin(), vec.end(), pred);
}

int main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	std::vector<MemeFighter*> t1 = {
		new MemeFrog("Dat Boi", new Fists),
		new MemeStoner("Good Guy Greg", new Bat),
		new MemeFrog("The WB Frog", new Knife),
		new MemeCat("Haz cheeseburger", new Knife)
	};
	std::vector<MemeFighter*> t2 = {
		new MemeStoner("Chong", new Fists),
		new MemeCat("NEDM", new Fists),
		new MemeStoner("Scumbag Steve", new Bat),
		new MemeFrog("Pepe", new Knife)
	};

	std::cout << "=====================================" << std::endl;
	std::cout << std::boolalpha << AreSameType(*t1[0], *t2[3]) << std::endl;
	std::cout << std::boolalpha << AreSameType(*t1[0], *t2[0]) << std::endl;
	std::cout << typeid(*t2[1]).name() << std::endl;
	std::cout << "=====================================" << std::endl;

	const auto alive_pred = [](MemeFighter* pf) { return pf->IsAlive(); };
	while (std::any_of(t1.begin(), t1.end(), alive_pred) && std::any_of(t2.begin(), t2.end(), alive_pred))
	{
		shuffle_partition(t1, alive_pred);
		shuffle_partition(t2, alive_pred);

		for (size_t i = 0; i < t1.size(); i++)
		{
			Engage(*t1[i], *t2[i]);
			DoSpecials(*t1[i], *t2[i]);
			std::cout << "------------------------------------" << std::endl;
		}
		std::cout << "=====================================" << std::endl;

		for (size_t i = 0; i < t1.size(); ++i)
		{
			t1[i]->Tick();
			t2[i]->Tick();
		}
		std::cout << "=====================================" << std::endl;

		std::cout << "Press any key to continue...";
		while (!_kbhit());
		int x = _getch();
		std::cout << std::endl << std::endl;
	}

	std::cout << "TEAM " << (std::any_of(t1.begin(), t1.end(), alive_pred) ? "ONE" : "TWO") << " is victorious!" << std::endl;

	for (size_t i = 0; i < t1.size(); ++i)
	{
		delete t1[i];
		delete t2[i];
	}

	while (!_kbhit());
	return 0;
}
