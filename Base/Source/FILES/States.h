#pragma once
#include "Character.h"
#include <string>
class State
{
public:
	State();
	virtual ~State();

	virtual void update(double dt, Character* character , Character*enemy){};
	std::string stateName;
};

