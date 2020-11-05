#define _CRT_SECURE_NO_WARNINGS
#include"Player.h"
#include "UpgradableProperty.h"
#include <cstring>
#include <iostream>
using namespace std;

Player::Player(char* nm, int pos, colour c, bool bk, bool iJ, int jC, float mn, bool jailcrd, int mP)
{
	name = new char[strlen(nm) + 1];
	strcpy(name, nm);
	position = pos;
	bankrupt = bk;
	inJail = iJ;
	jailCount = jC;
	money = mn;
	cl = c;
	properties = nullptr;
	Property_size = 0;
	jailCard = jailcrd;
	mortgageProperties = mP;
}

Player::~Player()
{
	for (int x = 0; x < Property_size; x++)
	{
		properties[x]->setOwner(nullptr);
	}
	delete[] name;
	delete[] properties;
}

void Player::AddProperty(Property* p)
{
	p->setOwner(this);

	checkDoubleRent(p);


	if (properties == nullptr)
	{
		properties = new Property*;
		*properties = p;
	}

	else
	{
		Property** temp;
		temp = new Property*[Property_size + 1];
		for (int x = 0; x < Property_size; x++)
		{
			temp[x] = properties[x];
		}
		temp[Property_size] = p;
		delete[] properties;
		properties = temp;
	}
	Property_size++;
}

char* Player::getName()
{
	return name;
}

int Player::getPosition()
{
	return position;
}

int Player::getPropertySize()
{
	return Property_size;
}

bool Player::getJailCard()
{
	return jailCard;
}

float Player::getMoney()
{
	return money;
}

colour Player::getcolour()
{
	return cl;
}

void Player::incposition(int p)
{
	if (position + p <= 39)
	{
		position += p;
	}
	else
	{
		position += p - 40;
		addMoney(500);
		system("pause");
	}
}

int Player::getMortgageProperties()
{
	return mortgageProperties;
}

void Player::setJailcard(bool b)
{
	jailCard = b;
}

void Player::addMoney(float m)
{
	money += m;
}

void Player::deductMoney(float m)
{
	money -= m;
}

void Player::setBankrupt()
{
	bankrupt = true;
}

void Player::setPosition(int p)
{
	position = p;
}

bool Player::getBankrupt()
{
	return bankrupt;
}

void Player::checkDoubleRent(Property* p)
{
	char* group = p->getGroup();
	int count = 0;

	if (group == "station" || group == "utility")
	{
		for (int x = 0; x < Property_size; x++)
		{
			if (!strcmp(properties[x]->getGroup(), group))
			{
				count++;
			}
		}
		if (count == 3)
		{
			p->doubleRent();
			for (int x = 0; x < Property_size; x++)
			{
				if (!strcmp(properties[x]->getGroup(), group))
				{
					properties[x]->doubleRent();
				}
			}
		}
	}
	else if (group == "johar")
	{
		for (int x = 0; x < Property_size; x++)
		{
			if (!strcmp(properties[x]->getGroup(), group))
			{
				count++;
			}
		}
		if (count == 1)
		{
			p->doubleRent();
			for (int x = 0; x < Property_size; x++)
			{
				if (!strcmp(properties[x]->getGroup(), group))
				{
					properties[x]->doubleRent();
					break;
				}
			}
		}
	}
	else
	{
		for (int x = 0; x < Property_size; x++)
		{
			if (!strcmp(properties[x]->getGroup(), group))
			{
				count++;
			}
		}
		if (count == 2)
		{
			p->doubleRent();
			for (int x = 0; x < Property_size; x++)
			{
				if (!strcmp(properties[x]->getGroup(), group))
				{
					properties[x]->doubleRent();
				}
			}
		}
	}
}

void Player::transferProperties(Player* p)
{
	for (int x = 0; x < Property_size; x++)
	{
		p->AddProperty(properties[x]);
	}
	delete[] properties;
	properties = nullptr;
}

bool Player::checkBankrupt(float r)
{
	float total = 0;
	//for (int x = 0; x < Property_size; x++)
	//{
	//	if (properties[x]->getMortgaged() != true)
	//	{
	//		total += properties[x]->calculateMortgage();
	//	}
	//}
	int umortgagedproperties = getUnMortgagedProperties();
	total += money;
	if (total < r && getUnMortgagedProperties()==0)
	{
		cout << name << " is bankrupt!" << endl;
		bankrupt = true;
		system("pause");
		return true;
	}
	return false;
}

int Player::getUnMortgagedProperties()
{
	int count = 0;
	for (int x = 0; x < Property_size; x++)
	{
		if (!properties[x]->getMortgaged())
		{
			count++;
		}
	}
	return count;
}

float Player::caluclateLandTax()
{
	float tax=0;
	for (int x = 0; x < Property_size; x++)
	{
		tax += properties[x]->getcost();
	}
	tax = tax * 20 / 100;
	return tax;
}

void Player::mortgageProperty()
{
	int option;
	system("cls");
	if (Property_size > mortgageProperties)
	{
		cout << "Select property to mortgage: " << endl;
		for (int x = 0; x < Property_size; x++)
		{
			if (!properties[x]->getMortgaged())
			{
				cout << x + 1 << ") " << properties[x]->getname() << "  Mortgage Value: " << properties[x]->calculateMortgage() << endl;
			}
		}
		cin >> option;
		properties[option - 1]->setMortgage(true);
		money += properties[option - 1]->calculateMortgage();
		mortgageProperties++;
	}
	else
	{
		cout << "You dont have any unmortgaged property!" << endl;
		system("pause");
	}
}

void Player::unMortgageProperty()
{
	int option;
	if (mortgageProperties != 0)
	{
		cout << "Select property to unmortgage: " << endl;
		for (int x = 0; x < Property_size; x++)
		{
			if (properties[x]->getMortgaged())
			{
				cout << x + 1 << ") " << properties[x]->getname() << "  Price to unmortgage: " << properties[x]->calculateMortgage()*120/100 << endl;
			}
		}
		cin >> option;
		if (money >= properties[option - 1]->calculateMortgage() * 120 / 100)
		{
			properties[option - 1]->setMortgage(false);
			money -= properties[option - 1]->calculateMortgage() * 120 / 100;
			mortgageProperties--;
		}
		else
		{
			cout << "You dont have enough money!" << endl;
		}
	}
	else
	{
		cout << "You dont have any mortgaged properties!" << endl;
	}
}

void Player::incJailCount()
{
	if (jailCount < 2)
	{
		jailCount++;
	}
	else
	{
		jailCount = 0;
	}
}

int Player::getJailCount()
{
	return jailCount;
}

const Property*const* Player::getProperties()
{
	return properties;
}

void Player::setInJail(bool b)
{
	inJail = b;
}

bool Player::getInJail()
{
	return inJail;
}

float Player::calculatePropertyTax()
{
	float tax = 0;
	for (int x = 0; x < Property_size; x++)
	{
		tax += properties[x]->getcost() * 10 / 100;
		if (properties[x]->getpropertytype() == 1)
		{
			UpgradableProperty* temp = dynamic_cast<UpgradableProperty*>(properties[x]);
			tax += temp->getHouse() * 100 * 20 / 100;
			tax += temp->getShop() * 300 * 30 / 100;
			tax += temp->getHotel() * 1000 * 30 / 100;
		}
	}
	return tax;
}

float Player::calculateStreetRepairCharges(int hs,int ho)
{
	float charges = 0;
	int houses = 0;
	int hotel = 0;
	for (int x = 0; x < Property_size; x++)
	{
		if (properties[x]->getpropertytype() == 1)
		{
			houses += dynamic_cast<UpgradableProperty*>(properties[x])->getHouse();
			hotel += dynamic_cast<UpgradableProperty*>(properties[x])->getHotel();
		}
	}
	charges = hs * houses;
	charges += ho * hotel;
	return charges;
}

char* Player::PropertyName(int x)
{
	return properties[x]->getname();
}

int Player::PropertyPos(int i)
{
	return properties[i]->getpos();
}

void Player::RemoveProperty(Property* p)
{
	if (Property_size == 1 && properties[0] == p)
	{
		delete[] properties;
		properties = nullptr;
	}
	else if (Property_size == 1)
	{
		return;
	}
	else
	{
		bool found = false;
		Property** temp = new Property*[Property_size - 1];
		for (int x = 0, y = 0; x < Property_size; x++)
		{
			if (properties[x] != p)
			{
				temp[y++] = properties[x];
			}
			else
			{
				found = true;
			}
		}
		if (found)
		{
			delete[] properties;
			properties = temp;
			Property_size--;
		}
		else
		{
			delete[] temp;
		}
	}
}

float Player::sellUpgrades(Property* p)
{
	char* group = p->getGroup();
	int count = 0;
	float total = 0;
	int arr[3], arrCount = 0;

	if (group == "station" || group == "utility")
	{
		return 0;
	}
	else if (group == "johar")
	{
		for (int x = 0; x < Property_size; x++)
		{
			if (!strcmp(properties[x]->getGroup(), group))
			{
				arr[arrCount++] = x;
				count++;
			}
		}
		if (count != 2)
		{
			return 0;
		}
	}
	else
	{
		for (int x = 0; x < Property_size; x++)
		{
			if (!strcmp(properties[x]->getGroup(), group))
			{
				count++;
			}
		}
		if (count != 3)
		{
			return 0;
		}
	}
	int wifi, gas, electricity, house, shop, hotel;

	for (int x = 0; x < arrCount; x++)
	{
		UpgradableProperty* upp = dynamic_cast<UpgradableProperty*>(properties[arr[x]]);
		wifi = upp->getWifi();
		gas = upp->getGas();
		electricity = upp->getElectricity();
		house = upp->getHouse();
		hotel = upp->getHotel();
		shop = upp->getShop();
		if (house != 0)
		{
			upp->decHouse(house);
		}
		if (hotel != 0)
		{
			upp->decHotel(hotel);
		}
		if (shop != 0)
		{
			upp->decShop(shop);
		}
		
		upp->setRentToDefault();
		
		total += 15 * wifi;
		total += 25 * electricity;
		total += 25 * gas;
		total += house * 50;
		total += shop * 150;
		total += hotel* 500;
	}
	money += total;
	return total;
}

void Player::sell(Player** pls,int size)
{
	int opt = 0;
	system("cls");
	cout << "Select property to sell" << endl;
	if (Property_size != 0)
	{
		for (int x = 0; x < Property_size; x++)
		{
			if (!properties[x]->getMortgaged())
			{
				cout <<x+1<< ") "<<properties[x]->getname() << endl;
			}
		}
		cin >> opt;
		float bid = 0;
		char option;
		int id = -1;
		b:
		float highest = 0;
		system("cls");
		properties[opt-1]->printProperty();
		cout << endl<<"Auction: " << endl;
		int x = 0;
		int count = 0;
		while (true)
		{
			if (pls[x] != this)
			{
				cout << pls[x]->getName() << " wants to bid?(y/n) ";
				cin >> option;
				if (option == 'y' || option == 'Y')
				{
					count = 0;
					cout << pls[x]->getName() << " cash: " << pls[x]->getMoney() << endl;
					cout << "Bid: ";
					cin >> bid;
					if (bid > highest)
					{
						highest = bid;
						id = x;
					}
					if (x + 1 >= size)
					{
						x = 0;
					}
					else
					{
						x++;
					}
				}
				else if (option == 'n' || option == 'N')
				{
					count++;
					if (x + 1 >= size)
					{
						x = 0;
					}
					else
					{
						x++;
					}
				}
				else
				{
					cout << "Invalid option!" << endl;
				}
				if (count == size)
				{
					break;
				}
			}
			else if (x + 1 >= size)
			{
				x = 0;
			}
			else
			{
				x++;
			}
		}
		if (id != -1)
		{
			if (pls[id]->getMoney() >= highest)
			{
				sellUpgrades(properties[opt - 1]);
				pls[id]->AddProperty(properties[opt-1]);
				pls[id]->deductMoney(highest);
				addMoney(highest);
				RemoveProperty(properties[opt-1]);
				cout << "Property purchased by " << pls[id]->getName()<<endl;
				system("pause");
			}
			else
			{
				cout << pls[id]->getName() << " doesnt have enough money!" << endl;
				system("pause");
				goto b;
			}
		}
	}
	else
	{
		cout << "You have no properties to sell!" << endl;
	}
}