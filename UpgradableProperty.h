#pragma once

#include"Upgrade.h"
#include "Property.h"

class UpgradableProperty:public Property
{
public:
	UpgradableProperty(char*,char*, int, int, float, float);
	~UpgradableProperty();
	void setWifi();
	void setGas();
	void setElectricity();
	void incHouse();
	void incHotel();
	void incShop();
	int getWifi();
	int getGas();
	int getElectricity();
	int getHouse();
	int getHotel();
	int getShop();
	void printProperty();
	void decHouse(int);
	void decShop(int);
	void decHotel(int);
	void upgrade();
private:
	Upgrade* shop;
	Upgrade* house;
	Upgrade* hotel;
	int hotel_size;
	int house_size;
	int shop_size;
};

