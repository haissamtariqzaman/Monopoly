#pragma once
#include "Player.h"

class Property
{
public:
	Property(char*,char*, int, int, float, float);
	virtual ~Property();
	char* getname();
	int getpos();
	int getpropertytype();
	float getcost();
	float getrent();
	char* getGroup();
	void doubleRent();
	void setOwner(Player*);
	Player* getOwner();
	bool getMortgaged();
	void setMortgage(bool);
	void setRentToDefault();
	float getDefaultRent();
	float calculateMortgage();
	void setRent(float);
	virtual void printProperty() = 0;
protected:
	char* name;
	char* group;
	int position;
	int property_type;
	float cost;
	float rent;
	float defaultRent;
	bool mortgaged;
	Player* owner;
};