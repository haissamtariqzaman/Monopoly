#include "NonUpgradable.h"

NonUpgradable::NonUpgradable(char* n,char* g, int p, int pt, float c, float r) :Property(n,g,p,pt,c,r)
{}

NonUpgradable::~NonUpgradable()
{}

void NonUpgradable::printProperty()
{
	Property::printProperty();
}