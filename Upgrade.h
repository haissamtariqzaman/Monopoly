#pragma once
#include"Utilities.h"

class Upgrade
{
public:
	Upgrade(bool=0,bool=0,bool=0);
	void setWifi(bool);
	void setGas(bool);
	void setElectricity(bool);
	bool getWifi();
	bool getGas();
	bool getElectricity();
private:
	Utilities u;
};