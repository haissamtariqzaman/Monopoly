#pragma once

struct colour
{
	int r, g, b;
};

class Property;

class Player
{
public:
	Player(char*, int, colour,bool=0,bool=0,int=0,float=5000,bool=0,int=0);
	void AddProperty(Property*);
	void RemoveProperty(Property*);
	char* getName();
	int getPosition();
	bool getJailCard();
	float getMoney();
	colour getcolour();
	void incposition(int);
	void setJailcard(bool);
	void setPosition(int);
	void addMoney(float);
	void deductMoney(float);
	void setBankrupt();
	bool getBankrupt();
	int getPropertySize();
	void transferProperties(Player*);
	int getMortgageProperties();
	int getUnMortgagedProperties();
	void mortgageProperty();
	void unMortgageProperty();
	void sell(Player**,int);
	bool checkBankrupt(float);
	void setInJail(bool);
	bool getInJail();
	void incJailCount();
	int getJailCount();
	float caluclateLandTax();
	float calculatePropertyTax();
	float calculateStreetRepairCharges(int,int);
	const Property*const* getProperties();
	char* PropertyName(int);
	int PropertyPos(int);
	~Player();
private:
	void checkDoubleRent(Property*);
	float sellUpgrades(Property*);
private:
	char* name;
	int position;
	bool bankrupt;
	Property** properties;
	int Property_size;
	bool jailCard;
	bool inJail;
	int jailCount;
	float money;
	colour cl;
	int mortgageProperties;
};
