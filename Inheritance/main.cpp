#include <iostream>
#include <string>

class Smasher
{
public:
	Smasher() = default;
	Smasher(int hp, int str, const std::string& name)
		: mHp(hp), mStr(str), mName(name)
	{}
	int GetStr() const
	{
		return mStr;
	}
	int GetHP() const
	{
		return mHp;
	}
	const std::string& GetName() const
	{
		return mName;
	}
	void Smash(Smasher& target) const
	{
		if (target.IsDead())
			std::cout << mName << " smashes " << target.GetName() << "'s dead body. Still dead.\n";
		else
		{
			std::cout << mName << " smashes " << target.GetName() << ".\n";
			target.TakeDamage(mStr);
		}
	}
	void TakeDamage(int damage)
	{
		std::cout << mName << " takes " << damage << " damage.\n";
		mHp -= damage;

		if (IsDead())
			std::cout << mName << " dies.\n";
	}
	bool IsDead() const
	{
		return mHp <= 0;
	}

protected:
	int mHp = 69;
	int mStr = 1;

private:
	std::string mName = "McDefault";
};

class EliteSmasher : public Smasher
{
public:
	EliteSmasher(int hp, int str, const std::string& name)
		: Smasher(hp, str, name)
	{}
	void SuperSmash(Smasher& target)
	{
		if (mSp >= 3)
		{
			if (target.IsDead())
				std::cout << GetName() << " uses super smash on " << target.GetName() << "'s dead body. Still dead.\n";
			else
			{
				std::cout << GetName() << " uses super smash on " << target.GetName() << ".\n";
				target.TakeDamage(GetStr() * 2);
			}
			mSp -= 3;
		}
		else
			std::cout << GetName() << " tried to use super smash on " << target.GetName() << ", but he didn't have enough goddamn sp.\n";
	}
	void Smash(Smasher& target)
	{
		Smasher::Smash(target);
		std::cout << GetName() << " recovers 2 sp.\n";
		mSp += 2;
	}
	void PepUp()
	{
		if (mSp >= 2)
		{
			std::cout << GetName() << " uses Pep Up and gains 30 hp and 10 str. His bones is so huge.\n";
			mHp += 30;
			mStr += 10;
			mSp -= 2;
		}
		else
			std::cout << GetName() << " tried to use Pep Up but lacks sp. Tremendously flaccid.\n";
	}

private:
	int mSp = 6;
};

int main()
{
	Smasher df(100, 30, "Dik Fuk");
	EliteSmasher tb(110, 13, "Cunt Destroyer");

	df.Smash(tb);

	tb.PepUp();
	tb.SuperSmash(df);
	tb.SuperSmash(df);
	tb.SuperSmash(df);
	tb.Smash(df);
	tb.Smash(df);
	tb.SuperSmash(df);
	tb.SuperSmash(df);

	std::cin.get();
	return 0;
}