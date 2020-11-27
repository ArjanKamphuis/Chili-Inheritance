#pragma once

#include "MemeFighter.h"

class MemeFrog : public MemeFighter
{
public:
	MemeFrog(const std::string& name);
	void SpecialMove(MemeFighter& other) override;
	void Tick() override;
};

