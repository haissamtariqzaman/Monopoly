#include "UpgradableProperty.h"
#include <iostream>
using namespace std;

UpgradableProperty::UpgradableProperty(char* n,char* g, int p, int pt, float c, float r) :Property(n,g, p, pt, c, r)
{
	shop = nullptr;
	house = nullptr;
	shop = nullptr;
	house_size = 0;
	shop_size = 0;
	hotel_size = 0;
}

void UpgradableProperty::setWifi()
{
	bool done=false;
	for (int x = 0; x < house_size; x++)
	{
		if (!house[x].getWifi())
		{
			house[x].setWifi(true);
			done = true;
			break;
		}
	}
	if (!done)
	{
		for (int x = 0; x < shop_size; x++)
		{
			if (!shop[x].getWifi())
			{
				shop[x].setWifi(true);
				done = true;
				break;
			}
		}
	}
	if (!done)
	{
		for (int x = 0; x < hotel_size; x++)
		{
			if (!hotel[x].getWifi())
			{
				hotel[x].setWifi(true);
				done = true;
				break;
			}
		}
	}
	rent += rent * 10 / 100;
}

void UpgradableProperty::setGas()
{
	bool done = false;
	for (int x = 0; x < house_size; x++)
	{
		if (!house[x].getGas())
		{
			house[x].setGas(true);
			done = true;
			break;
		}
	}
	if (!done)
	{
		for (int x = 0; x < shop_size; x++)
		{
			if (!shop[x].getGas())
			{
				shop[x].setGas(true);
				done = true;
				break;
			}
		}
	}
	if (!done)
	{
		for (int x = 0; x < hotel_size; x++)
		{
			if (!hotel[x].getGas())
			{
				hotel[x].setGas(true);
				done = true;
				break;
			}
		}
	}
	rent += rent * 20 / 100;
}

void UpgradableProperty::setElectricity()
{
	bool done = false;
	for (int x = 0; x < house_size; x++)
	{
		if (!house[x].getElectricity())
		{
			house[x].setElectricity(true);
			done = true;
			break;
		}
	}
	if (!done)
	{
		for (int x = 0; x < shop_size; x++)
		{
			if (!shop[x].getElectricity())
			{
				shop[x].setElectricity(true);
				done = true;
				break;
			}
		}
	}
	if (!done)
	{
		for (int x = 0; x < hotel_size; x++)
		{
			if (!hotel[x].getElectricity())
			{
				hotel[x].setElectricity(true);
				done = true;
				break;
			}
		}
	}
	rent += rent * 20 / 100;
}

void UpgradableProperty::incHouse()
{
	if (house == nullptr)
	{
		house = new Upgrade;
	}
	else
	{
		Upgrade* temp=new Upgrade[house_size+1];
		for (int x = 0; x < house_size; x++)
		{
			temp[x] = house[x];
		}
		delete[] house;
		house = temp;
	}
	house_size++;
	rent += rent * 30 / 100;
}

void UpgradableProperty::incHotel()
{
	if (hotel == nullptr)
	{
		hotel = new Upgrade;
	}
	else
	{
		Upgrade* temp = new Upgrade[hotel_size + 1];
		for (int x = 0; x < hotel_size; x++)
		{
			temp[x] = hotel[x];
		}
		delete[] hotel;
		hotel = temp;
	}
	hotel_size++;
	rent += rent * 80 / 100;
}

void UpgradableProperty::incShop()
{
	if (shop == nullptr)
	{
		shop = new Upgrade;
	}
	else
	{
		Upgrade* temp = new Upgrade[shop_size + 1];
		for (int x = 0; x < shop_size; x++)
		{
			temp[x] = shop[x];
		}
		delete[] shop;
		shop = temp;
	}
	shop_size++;
	rent += rent * 60 / 100;
}

int UpgradableProperty::getWifi()
{
	int count = 0;
	for (int x = 0; x < house_size; x++)
	{
		if (house[x].getWifi())
		{
			count++;
		}
	}
	for (int x = 0; x < shop_size; x++)
	{
		if (shop[x].getWifi())
		{
			count++;
		}
	}
	for (int x = 0; x < hotel_size; x++)
	{
		if (hotel[x].getWifi())
		{
			count++;
		}
	}
	return count;
}

int UpgradableProperty::getGas()
{
	int count = 0;
	for (int x = 0; x < house_size; x++)
	{
		if (house[x].getGas())
		{
			count++;
		}
	}
	for (int x = 0; x < shop_size; x++)
	{
		if (shop[x].getGas())
		{
			count++;
		}
	}
	for (int x = 0; x < hotel_size; x++)
	{
		if (hotel[x].getGas())
		{
			count++;
		}
	}
	return count;
}

int UpgradableProperty::getElectricity()
{
	int count = 0;
	for (int x = 0; x < house_size; x++)
	{
		if (house[x].getElectricity())
		{
			count++;
		}
	}
	for (int x = 0; x < shop_size; x++)
	{
		if (shop[x].getElectricity())
		{
			count++;
		}
	}
	for (int x = 0; x < hotel_size; x++)
	{
		if (hotel[x].getElectricity())
		{
			count++;
		}
	}
	return count;
}

int UpgradableProperty::getHouse()
{
	return house_size;
}

int UpgradableProperty::getHotel()
{
	return hotel_size;
}

int UpgradableProperty::getShop()
{
	return shop_size;
}

void UpgradableProperty::printProperty()
{
	Property::printProperty();
	if (owner != nullptr)
	{
		cout << "Upgrades: " << endl;
		cout << "Hotels: " << hotel_size << endl;
		cout << "Houses: " << house_size << endl;
		cout << "Shops: " << shop_size << endl;
		cout << "Wifi: " << getWifi()<< endl;
		cout << "Gas: " << getGas() << endl;
		cout << "Electricity: " << getElectricity() << endl;
	}
}

void UpgradableProperty::decHouse(int i)
{
	if (i == house_size)
	{
		delete[] house;
		house = nullptr;
	}
	else
	{
		Upgrade* temp = new Upgrade[house_size - 1];
		for (int x = 0; x < house_size - 1; x++)
		{
			temp[x] = house[x];
		}
		delete[] house;
		house = temp;
	}
	house_size -= i;
}

void UpgradableProperty::decShop(int i)
{
	if (i == shop_size)
	{
		delete[] shop;
		shop = nullptr;
	}
	else
	{
		Upgrade* temp = new Upgrade[shop_size - 1];
		for (int x = 0; x < shop_size - 1; x++)
		{
			temp[x] = shop[x];
		}
		delete[] shop;
		shop = temp;
	}
	shop_size -= i;
}

void UpgradableProperty::decHotel(int i)
{
	if (i == hotel_size)
	{
		delete[] hotel;
		hotel = nullptr;
	}
	else
	{
		Upgrade* temp = new Upgrade[hotel_size - 1];
		for (int x = 0; x < hotel_size - 1; x++)
		{
			temp[x] = hotel[x];
		}
		delete[] hotel;
		hotel = temp;
	}
	hotel_size -= i;
}

void UpgradableProperty::upgrade()
{
	
}

UpgradableProperty::~UpgradableProperty()
{
	if (house != nullptr)
	{
		delete[] house;
	}
	if (shop != nullptr)
	{
		delete[] shop;
	}
	if (hotel != nullptr)
	{
		delete[] hotel;
	}
}