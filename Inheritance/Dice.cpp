#include "Dice.h"

int Dice::Roll(int nDice)
{
	int total = 0;
	for (int n = 0; n < nDice; n++)
		total += mD6(mRng);
	return total;
}
