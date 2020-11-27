#pragma once

#include "MemeFighter.h"

class MemeStoner : public MemeFighter
{
public:
	MemeStoner(const std::string& name);
	void SpecialMove(MemeFighter&) override;
};

