#include "Upgrade.h"

Upgrade::Upgrade(bool w, bool g, bool e) :u(w, g, e)
{}

void Upgrade::setWifi(bool w)
{
	u.setWifi(w);
}
void Upgrade::setGas(bool g)
{
	u.setGas(g);
}
void Upgrade::setElectricity(bool e)
{
	u.setElectricity(e);
}
bool Upgrade::getWifi()
{
	return u.getWifi();
}
bool Upgrade::getGas()
{
	return u.getGas();
}
bool Upgrade::getElectricity()
{
	return u.getElectricity();
}