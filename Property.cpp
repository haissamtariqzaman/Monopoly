#define _CRT_SECURE_NO_WARNINGS
#include"Property.h"
#include "UpgradableProperty.h"
#include <iostream>
#include <cstring>
using namespace std;

Property::Property(char* n, char* g, int p, int pt, float c, float r)
{
	name = new char[strlen(n) + 1];
	strcpy(name, n);
	group = new char[strlen(g) + 1];
	strcpy(group, g);
	position = p;
	property_type = pt;
	rent = r;
	defaultRent = r;
	cost = c;
	owner = nullptr;
	mortgaged = false;
}

Property::~Property()
{
	delete[] name;
	delete[] group;
}

char* Property::getname()
{
	return name;
}

int Property::getpos()
{
	return position;
}

int Property::getpropertytype()
{
	return property_type;
}

float Property::getcost()
{
	return cost;
}

float Property::getrent()
{
	return rent;
}

char* Property::getGroup()
{
	return group;
}

void Property::setOwner(Player* p)
{
	owner = p;
}

void Property::setRentToDefault()
{
	rent = defaultRent;
}

void Property::setRent(float r)
{
	rent = r;
}

void Property::printProperty()
{
	cout << "Propert Name: " << name << endl;
	cout << "Group: " << group << endl;
	cout << "Owner: " << ((owner == nullptr) ? "No" : owner->getName() )<< endl;
	if (owner == nullptr)
	{
		cout << "Cost: " << cost << endl;
	}
	cout << "Rent: " << rent << endl;
}

void Property::doubleRent()
{
	rent *= 2;
}

Player* Property::getOwner()
{
	return owner;
}

bool Property::getMortgaged()
{
	return mortgaged;
}

void Property::setMortgage(bool m)
{
	mortgaged = m;
}

float Property::calculateMortgage()
{
	float total = cost / 2;
	if (property_type == 1)
	{
		UpgradableProperty* temp = dynamic_cast<UpgradableProperty*>(this);
		total += 15 * temp->getWifi();
		total += 25 * temp->getElectricity();
		total += 25 * temp->getGas();
		total += temp->getHouse() * 50;
		total += temp->getShop() * 150;
		total += temp->getHotel() * 500;
	}
	return total;
}

float Property::getDefaultRent()
{
	return defaultRent;
}