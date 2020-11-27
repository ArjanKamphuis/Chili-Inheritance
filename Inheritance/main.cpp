#include <algorithm>
#include <conio.h>
#include <iostream>

#include "MemeFighter.h"
#include "MemeFrog.h"
#include "MemeStoner.h"

#ifdef _DEBUG
#include <crtdbg.h>
#endif

void Engage(MemeFighter& f1, MemeFighter& f2)
{
	MemeFighter* p1 = &f1;
	MemeFighter* p2 = &f2;

	if (p1->GetInitiative() < p2->GetInitiative())
		std::swap(p1, p2);

	p1->Punch(*p2);
	p2->Punch(*p1);
}

void DoSpecials(MemeFighter& f1, MemeFighter& f2)
{
	MemeFighter* p1 = &f1;
	MemeFighter* p2 = &f2;

	if (p1->GetInitiative() < p2->GetInitiative())
		std::swap(p1, p2);

	p1->SpecialMove(*p2);
	p2->SpecialMove(*p1);
}

template<typename T, class P>
void shuffle_partition(std::vector<T>& vec, P pred)
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
		new MemeFrog("Dat Boi"),
		new MemeStoner("Good Guy Greg"),
		new MemeFrog("The WB Frog")
	};
	std::vector<MemeFighter*> t2 = {
		new MemeStoner("Chong"),
		new MemeStoner("Scumbag Steve"),
		new MemeFrog("Pepe")
	};

	std::cout << std::endl;

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
