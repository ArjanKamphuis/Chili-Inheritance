#include <algorithm>
#include <conio.h>
#include <iostream>
#include <random>
#include <string>

class Dice
{
public:
	int Roll(int nDice)
	{
		int total = 0;
		for (int n = 0; n < nDice; n++)
			total += mD6(mRng);
		return total;
	}

private:
	std::uniform_int_distribution<int> mD6 = std::uniform_int_distribution<int>(1, 6);
	std::mt19937 mRng = std::mt19937(std::random_device{}());
};

class MemeFighter
{
public:
	const std::string& GetName() const
	{
		return mName;
	}
	int GetInitiative() const
	{
		return mSpeed + Roll(2);
	}
	bool IsAlive() const
	{
		return mHp > 0;
	}
	void Punch(MemeFighter& other)
	{
		if (IsAlive() && other.IsAlive())
		{
			std::cout << mName << " punches " << other.mName << "!" << std::endl;
			ApplyDamageTo(other, mPower + Roll(2));
		}
	}
	virtual void SpecialMove(MemeFighter&) = 0;
	void Tick()
	{
		if (IsAlive())
		{
			const int recovery = Roll();
			std::cout << mName << " recovers " << recovery << " HP." << std::endl;
			mHp += recovery;
		}
	}

protected:
	MemeFighter(const std::string& name, int hp, int speed, int power)
		: mName(name), mHp(hp), mSpeed(speed), mPower(power)
	{
		std::cout << name << " enters the ring!" << std::endl;
	}
	void ApplyDamageTo(MemeFighter& target, int damage) const
	{
		target.mHp -= damage;
		std::cout << target.mName << " takes " << damage << " damage." << std::endl;
		if (!target.IsAlive())
			std::cout << "As the life leaves " << target.mName << "'s body, so does the poop." << std::endl;
	}
	int Roll(int nDice = 1) const
	{
		return mDice.Roll(nDice);
	}

protected:
	int mHp;
	int mSpeed;
	int mPower;
	std::string mName;

private:
	mutable Dice mDice;
};

class MemeFrog : public MemeFighter
{
public:
	MemeFrog(const std::string& name)
		: MemeFighter(name, 69, 7, 14)
	{}
	void SpecialMove(MemeFighter& other) override
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
	void Tick()
	{
		if (IsAlive())
		{
			std::cout << mName << " is hurt by the bad AIDS!" << std::endl;
			ApplyDamageTo(*this, Roll());
			MemeFighter::Tick();
		}
	}
};

class MemeStoner : public MemeFighter
{
public:
	MemeStoner(const std::string& name)
		: MemeFighter(name, 80, 4, 10)
	{}
	void SpecialMove(MemeFighter&) override
	{
		if (IsAlive())
		{
			if (Roll() > 3)
			{
				std::cout << mName << " smokes the dank sticky icky, becoming Super " << mName << std::endl;
				mName = "Super " + mName;
				mSpeed += 3;
				mPower = (mPower * 69) / 42;
				mHp += 10;
			}
			else
				std::cout << mName << " spaces out." << std::endl;
		}
	}
};

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
	MemeFrog f1("Dat Boi");
	MemeStoner f2("Good Guy Greg");
	MemeFrog f3("The WB Frog");

	MemeStoner g1("Chong");
	MemeStoner g2("Scumbag Steve");
	MemeFrog g3("Pepe");

	std::vector<MemeFighter*> t1 = { &f1, &f2, &f3 };
	std::vector<MemeFighter*> t2 = { &g1, &g2, &g3 };

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

	std::cout << "TEAM " << (std::any_of(t1.begin(), t1.end(), alive_pred) ? "ONE" : "TWO") << " is victorious!";

	while (!_kbhit());
	return 0;
}
