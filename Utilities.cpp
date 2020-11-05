#include "Utilities.h"

Utilities::Utilities(bool w, bool g, bool e)
{
	wifi = w;
	gas = g;
	electricity = e;
}

void Utilities::setWifi(bool x)
{
	wifi = x;
}
void Utilities::setGas(bool x)
{
	gas = x;
}
void Utilities::setElectricity(bool x)
{
	electricity = x;
}
bool Utilities::getWifi()
{
	return wifi;
}
bool Utilities::getGas()
{
	return gas;
}
bool Utilities::getElectricity()
{
	return electricity;
}