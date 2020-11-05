#pragma once

#include "Property.h"

class NonUpgradable:public Property
{
public:
	NonUpgradable(char*,char*, int, int, float, float);
	~NonUpgradable();
	void printProperty();
private:
};
