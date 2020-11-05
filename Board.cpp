#include "Board.h"
#include "UpgradableProperty.h"
#include "NonUpgradable.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string>
#include <cstring>
#include "myconsole.h"
#include "mygraphics.h"
using namespace std;

void pause() 
{
	cin.clear();
	cout << endl << "Enter c to continue...";
	cin.ignore(1000,'c');
}

Board::Board(int s) :communityChest("CommunityChest.txt"), chance("Chance.txt")
{
	char option='\0';
	u:
	cout << "N) New Game" << endl;
	cout << "L) Load Game" << endl;
	cin >> option;
	cin.ignore();
	if (option == 'l' || option == 'L')
	{
		load();
	}
	else if (option == 'n' || option == 'N')
	{
		turn = 0;
		playerSize = s;
		players = new Player*[playerSize];
		for (int x = 0; x < playerSize; x++)
		{
			char name[30];
			colour cl;
			if (x == 0)
			{
				cl.r = 32;
				cl.g = 178;
				cl.b = 170;
				cout << "Enter player " << x + 1 << " name: ";
				cin.getline(name, 30);
				players[x] = new Player(name, 0, cl);
			}
			else if (x == 1)
			{
				cl.r = 255;
				cl.g = 105;
				cl.b = 193;
				cout << "Enter player " << x + 1 << " name: ";
				cin.getline(name, 30);
				players[x] = new Player(name, 0, cl);
			}
			else if (x == 2)
			{
				cl.r = 192;
				cl.g = 192;
				cl.b = 192;
				cout << "Enter player " << x + 1 << " name: ";
				cin.getline(name, 30);
				players[x] = new Player(name, 0, cl);
			}
			else
			{
				cl.r = 0;
				cl.g = 0;
				cl.b = 0;
				cout << "Enter player " << x + 1 << " name: ";
				cin.getline(name, 30);
				players[x] = new Player(name, 0, cl);
			}
		}

		properties = new Property*[28];

		ifstream file;
		file.open("Properties.txt");

		if (file.is_open())
		{
			char pname[30];
			char group[20];
			int pos, type;
			float price, rent;
			for (int x = 0; x < 28; x++)
			{
				file.getline(pname, 30, ',');
				file.ignore();
				file.getline(group, 20, ',');
				file >> pos;
				file.ignore();
				file >> type;
				file.ignore();
				file >> price;
				file.ignore();
				file >> rent;
				file.ignore();
				if (type == 1)
				{
					properties[x] = new UpgradableProperty(pname, group, pos, type, price, rent);
				}
				else
				{
					properties[x] = new NonUpgradable(pname, group, pos, type, price, rent);
				}
			}
		}
		dice = 1;
	}
	else
	{
		cout << "Invalid option!" << endl;
		goto u;
	}
	communityChest.shuffle();
	chance.shuffle();
}

void Board::play()
{
	char option;
	//reprint();
	while (true)
	{
		if (checkWinner())
		{
			cout << players[0]->getName() << " wins!" << endl;
			pause();
			break;
		}
		if (players[turn]->getInJail())
		{
			if (players[turn]->getJailCount() < 2)
			{
				players[turn]->incJailCount();
				cout << players[turn]->getName() << " is in jail! Turn skipped" << endl;
				pause();
				nextTurn();
			}
			else
			{
				players[turn]->incJailCount(); //sets jailCount to 0 here
				players[turn]->setInJail(false);
			}
		}
		c:
		system("cls"); 
		reprint();
		//reprint();
		cout << players[turn]->getName() << ": " << endl;
		cout << endl;
		cout << "R) Roll dice" << endl;
		cout << "U) Upgrade Property" << endl;
		cout << "M) Unmortgage Property" << endl;
		cout << "S) Save and exit" << endl;
		cin >> option;
		if (option == 'r' || option == 'R')
		{
			rollDice();
			reprint(true);
			pause();
			int previousPosition = players[turn]->getPosition();
			players[turn]->incposition(dice);
			reprint();
			if (previousPosition > players[turn]->getPosition())
			{
				cout << players[turn]->getName() << " collected 500 from bank!" << endl;
				pause();
			}
		}
		else if (option == 's' || option == 'S')
		{
			save();
			break;
		}
		else if (option == 'u' || option == 'U')
		{
			upgrade();
			goto c;
		}
		else if (option == 'm' || option == 'M')
		{
			players[turn]->unMortgageProperty();
			pause();
			goto c;
		}
		else
		{
			cout << "Invalid option!" << endl;
			goto c;
		}
		//reprint();
		int x = players[turn]->getPosition();
		if (x != 2 && x != 4 && x != 7 && x != 10 && x != 17 && x != 20 && x != 22 && x != 30 && x != 33 && x != 36 && x != 38 && x != 0)
		{
			playerOnProperty(x);
		}
		else if (x == 4)
		{
			playerOnLandTax();
		}
		else if (x == 20)
		{
			playerOnParking();
		}
		else if (x == 30)
		{
			playerOnGoToPrison();
		}
		else if (x == 38)
		{
			playerOnPropertyTax();
		}
		else if (x == 2 || x == 17 || x == 33)
		{
			playerOnCommunityChest();
		}
		else if (x == 7 || x == 22 || x == 36)
		{
			playerOnChance();
		}
		nextTurn();
	}
}

void Board::playerOnGoToPrison()
{
	players[turn]->setPosition(10);
	char option;
	e:
	system("cls"); reprint();
	cout << players[turn]->getName() << ": " << endl;
	cout << "Cash: " << players[turn]->getMoney() << endl;
	cout << "Jail!" << endl;
	cout << endl;
	cout << "P) Pay 400 fine" << endl;
	cout << "U) Use jail card" << endl;
	cout << "C) Continue" << endl;
	cin >> option;
	if (option == 'p' || option == 'P')
	{
		if (players[turn]->getMoney() >= 400)
		{
			players[turn]->deductMoney(400);
			//reprint();
		}
		else
		{
			cout << "You dont have enough money!" << endl;
			pause();
			goto e;
		}
	}
	else if (option == 'u' || option == 'U')
	{
		if (players[turn]->getJailCard())
		{
			players[turn]->setJailcard(false);
		}
		else
		{
			cout << "You dont have a jail card!" << endl;
			pause();
			goto e;
		}
	}
	else if (option == 'c' || option == 'C')
	{
		players[turn]->setInJail(true);
	}
	else
	{
		cout << "Invalid option selected!" << endl;
		pause();
		goto e;
	}
	reprint();
}

void Board::playerOnParking()
{
	char option;
	bool bankrupt = players[turn]->checkBankrupt(10);
	if (bankrupt == true)
	{
		bankruptToBank();
	}
	else
	{
		e:
		system("cls"); reprint();
		cout << players[turn]->getName() << ": " << endl;
		cout << "Cash: " << players[turn]->getMoney() << endl;
		cout << "Parking Fee: 10" << endl;
		cout << endl;
		cout << "P) Pay Parking Fee" << endl;
		cout << "M) Mortgage Property"<<endl;
		cout << "S) Sell Property" << endl;
		cin >> option;
		if (option == 'p' || option == 'P')
		{
			if (players[turn]->getMoney() >= 10)
			{
				players[turn]->deductMoney(10);
				reprint();
			}
			else
			{
				cout << "You do not have enough money!" << endl;
				goto e;
			}
		}
		else if (option == 'm' || option == 'M')
		{
			players[turn]->mortgageProperty();
			reprint();
			goto e;
		}
		else if (option == 's' || option == 'S')
		{
			players[turn]->sell(players, playerSize);
			reprint();
			goto e;
		}
		else
		{
			cout << "Invalid option!" << endl;
			goto e;
		}
	}
}

void Board::playerOnLandTax()
{
	char option;
	float tax = players[turn]->caluclateLandTax();
	bool bankrupt = players[turn]->checkBankrupt(tax);
	if (bankrupt == true)
	{
		bankruptToBank();
	}
	else
	{
		d:
		system("cls"); reprint();
		cout << players[turn]->getName() << ": " << endl;
		cout << "Cash: " << players[turn]->getMoney() << endl;
		cout << "Land Tax: " << tax << endl;
		cout << endl;
		cout << "P) Pay Land Tax" << endl;
		cout << "M) Mortgage Property"<<endl;
		cout << "S) Sell Property" << endl;
		cin >> option;
		if (option == 'p' || option == 'P')
		{
			if (players[turn]->getMoney() >= tax)
			{
				players[turn]->deductMoney(tax);
				reprint();
			}
			else
			{
				cout << "You do not have enough money!" << endl;
				pause();
				goto d;
			}
		}
		else if (option == 'm' || option == 'M')
		{
			players[turn]->mortgageProperty();
			reprint();
			goto d;
		}
		else if (option == 's' || option == 'S')
		{
			players[turn]->sell(players, playerSize);
			reprint();
			goto d;
		}
		else
		{
			cout << "Invalid option!" << endl;
			goto d;
		}
	}
}

bool Board::bankruptToBank()
{
	const Property*const* prs = players[turn]->getProperties();
	int size = players[turn]->getPropertySize();
	removePlayer(turn);
	if (checkWinner())
	{
		return true;
	}
	cout << "All properties of " << players[turn]->getName() << " will be auctioned!" << endl;
	pause();
	for (int x = 0,y=0; y < size; x++)
	{
		if (properties[x] == prs[y])
		{
			Auction(properties[x]);
			y++;
			x = -1;
		}
	}
	return false;
}

void Board::playerOnProperty(int pos)
{
	char option;
	int op;
	Property* pr = findProperty(pos);

	a:
	system("cls"); reprint();
	cout << players[turn]->getName() << endl;
	cout << "Cash: " << players[turn]->getMoney() << endl;
	pr->printProperty();
	if (pr->getOwner() == players[turn])
	{
		cout << endl;
		cout << "C) Continue" << endl;
		cin >> option;
		if (option == 'c' || option == 'C')
		{}
		else
		{
			cout << "Invalid option!" << endl;
			pause();
			goto a;
		}
	}
	else if (pr->getOwner() == nullptr)
	{
		cout << endl;
		cout << "B) Buy Property" << endl;
		cout << "C) Continue" << endl;
		cin >> option;
		if (option == 'B' || option == 'b')
		{
			if (players[turn]->getMoney() >= pr->getcost())
			{
				players[turn]->AddProperty(pr);
				players[turn]->deductMoney(pr->getcost());
				system("cls"); reprint();
				//reprint();
				cout << "Property Purchased!" << endl;
				pr->printProperty();
				pause();
			}
			else
			{
				cout << "You dont have enough money!" << endl;
				pause();
				goto a;
			}
		}
		else if (option=='c' || option=='C')
		{
			Auction(pr);
		}
		else
		{
			cout << "Invalid option!" << endl;
			pause();
			goto a;
		}
		pause();
	}
	else if (pr->getOwner()!=players[turn])
	{
		if (!pr->getMortgaged())
		{
			Player* owner = pr->getOwner();
			float money = players[turn]->getMoney();
			float rent = pr->getrent();
			bool bankrupt = players[turn]->checkBankrupt(rent);

			if (bankrupt == true)
			{
				players[turn]->transferProperties(owner);
				removePlayer(turn);
				reprint();
			}
			else
			{
				cout << endl;
				cout << "P) Pay Rent" << endl;
				cout << "M) Mortgage Property" << endl;
				cout << "S) Sell Property" << endl;
				cin >> option;

				if (option == 'p' || option == 'P')
				{
					if ((money - rent) >= 0)
					{
						players[turn]->deductMoney(rent);
						owner->addMoney(rent);
						reprint();
						cout << "You paid RS" << rent << " as rent" << endl;
						pause();
					}
					else
					{
						cout << "You dont have enough money!" << endl;
						pause();
						goto a;
					}

				}

				else if (option == 'M' || option == 'm')
				{
					players[turn]->mortgageProperty();
					reprint();
					goto a;
				}
				else if (option == 's' || option == 'S')
				{
					players[turn]->sell(players, playerSize);
					reprint();
					goto a;
				}
				else
				{
					cout << "Invalid Option!" << endl;
					pause();
					goto a;
				}

			}
		}
		else
		{
			cout << "This property is mortgaged" << endl;
			pause();
		}
	}
}

void Board::removePlayer(int index)
{
	Player** temp;
	temp = new Player*[playerSize - 1];
	for (int x = 0,y=0; x < playerSize; x++)
	{
		if (x != index)
		{
			temp[y++] = players[x];
		}
	}
	delete[] players;
	players = temp;
	playerSize--;
}

bool Board::checkWinner()
{
	if (playerSize == 1)
	{
		pause();
		return true;
	}
	return false;
}

void Board::Auction(Property* p)
{
	float bid=0;
	char option;
	int id=-1;
	b:
	float highest = 0;
	system("cls"); reprint();
	p->printProperty();
	cout << "Auction: " << endl;
	int x=0;
	int count = 0;
	while (true)
	{
		cout << players[x]->getName() << " wants to bid?(y/n) ";
		cin >> option;
		if (option=='y' || option=='Y')
		{
			count = 0;
			cout << players[x]->getName() << " cash: " << players[x]->getMoney()<<endl;
			cout << "Bid: ";
			cin >> bid;
			if (bid > highest)
			{
				highest = bid;
				id = x;
			}
			if (x + 1 >= playerSize)
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
			if (x + 1 >= playerSize)
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
		if (count == playerSize)
		{
			break;
		}
	}
	if (id != -1)
	{
		if (players[id]->getMoney() >= highest)
		{
			players[id]->AddProperty(p);
			players[id]->deductMoney(highest);
			cout << "Property purchased by " << players[id]->getName() << endl;
			reprint();
		}
		else
		{
			cout << players[id]->getName() << " doesnt have enough money!" << endl;
			pause();
			goto b;
		}
	}
}

Property* Board::findProperty(int i)
{
	for (int x = 0; x < 28; x++)
	{
		if (properties[x]->getpos() == i)
		{
			return properties[x];
		}
	}
	return nullptr;
}

void Board::nextTurn()
{
	if (turn + 1 == playerSize)
	{
		turn = 0;
	}
	else
	{
		turn++;
	}
}

void Board::rollDice()
{
	srand(time(0));
	dice = (rand() % 6) + 1;
}

void Board::reprint(bool rd)
{
	int boardx = 400;
	int boardy = 16;
	if (!rd)
	{
		ClearScreen();

		display_Board(boardx, boardy);
		display_playerInfo(players, playerSize, boardx, boardy);
		for (int x = 0; x < playerSize; x++)
		{
			//int pos = players[x]->getPosition();
			//for (int i = 0; i < playerSize; i++)
			//{
			//	if (i!=x&&players[i]->getPosition() == pos)
			//	{
			//		r += 5;
			//		break;
			//	}
			//}
			display_player(players[x]->getPosition(), players[x]->getcolour().r, players[x]->getcolour().g, players[x]->getcolour().b, boardx, boardy, x * 5);
		}
	}
	else
	{
		for (int i = 0; i < 2; i++)
		{
			for (int x = 1; x < 7; x++)
			{
				printDice(x, 100, boardy);
				Sleep(60);
			}
		}
	}
	printDice(dice, 100, boardy);
}

void Board::printDice(int num, int x, int y)
{
	myRect(x + 700, y + 150, x + 750, y + 200, RGB(0,0,0), RGB(0,0,0));
	if (num == 1)
	{
		myEllipse(x + 720, y + 170, x + 730, y + 180, RGB(255,255,255), RGB(255,255,255));
	}
	else if (num == 2)
	{
		myEllipse(x + 710, y + 170, x + 720, y + 180, RGB(255, 255, 255), RGB(255, 255, 255));
		myEllipse(x + 730, y + 170, x + 740, y + 180, RGB(255, 255, 255), RGB(255, 255, 255));
	}
	else if (num == 3)
	{
		myEllipse(x + 720, y + 170, x + 730, y + 180, RGB(255, 255, 255), RGB(255, 255, 255));
		myEllipse(x + 705, y + 155, x + 715, y + 165, RGB(255, 255, 255), RGB(255, 255, 255));
		myEllipse(x + 735, y + 185, x + 745, y + 195, RGB(255, 255, 255), RGB(255, 255, 255));
	}
	else if (num == 4)
	{
		myEllipse(x + 705, y + 155, x + 715, y + 165, RGB(255, 255, 255), RGB(255, 255, 255));
		myEllipse(x + 735, y + 185, x + 745, y + 195, RGB(255, 255, 255), RGB(255, 255, 255));
		myEllipse(x + 735, y + 155, x + 745, y + 165, RGB(255, 255, 255), RGB(255, 255, 255));
		myEllipse(x + 705, y + 185, x + 715, y + 195, RGB(255, 255, 255), RGB(255, 255, 255));
	}
	else if (num == 5)
	{
		myEllipse(x + 720, y + 170, x + 730, y + 180, RGB(255, 255, 255), RGB(255, 255, 255));
		myEllipse(x + 705, y + 155, x + 715, y + 165, RGB(255, 255, 255), RGB(255, 255, 255));
		myEllipse(x + 735, y + 185, x + 745, y + 195, RGB(255, 255, 255), RGB(255, 255, 255));
		myEllipse(x + 735, y + 155, x + 745, y + 165, RGB(255, 255, 255), RGB(255, 255, 255));
		myEllipse(x + 705, y + 185, x + 715, y + 195, RGB(255, 255, 255), RGB(255, 255, 255));
	}
	else if (num == 6)
	{
		myEllipse(x + 705, y + 155, x + 715, y + 165, RGB(255, 255, 255), RGB(255, 255, 255));
		myEllipse(x + 735, y + 185, x + 745, y + 195, RGB(255, 255, 255), RGB(255, 255, 255));
		myEllipse(x + 735, y + 155, x + 745, y + 165, RGB(255, 255, 255), RGB(255, 255, 255));
		myEllipse(x + 705, y + 185, x + 715, y + 195, RGB(255, 255, 255), RGB(255, 255, 255));
		myEllipse(x + 705, y + 170, x + 715, y + 180, RGB(255, 255, 255), RGB(255, 255, 255));
		myEllipse(x + 735, y + 170, x + 745, y + 180, RGB(255, 255, 255), RGB(255, 255, 255));
	}
}

void Board::display_player(int n, int r, int g, int b, int x, int y,int sub)
{
	if (n >= 0 && n <= 10)
	{
		myEllipse((n * 84) + x + 68-sub, y + 30-sub, (n * 84) + x + 88-sub, y + 50-sub, RGB(r, g, b), RGB(r, g, b));
	}
	else if (n > 10 && n <= 20)
	{
		myEllipse(x + 928 - sub, ((n - 11) * 54) + y + 107 - sub, x + 948 - sub, ((n - 11) * 54) + y + 127 - sub, RGB(r, g, b), RGB(r, g, b));
	}
	else if (n > 20 && n <= 30)
	{
		myEllipse(x + 824 - ((n - 21) * 84) - sub, y + 623 - sub, x + 844 - ((n - 21) * 84) - sub, y + 643 - sub, RGB(r, g, b), RGB(r, g, b));
	}
	else if (n > 30 && n < 40)
	{
		myEllipse(x + 50 - sub, y + 539 - ((n - 31) * 54) - sub, x + 70 - sub, y + 559 - ((n - 31) * 54) - sub, RGB(r, g, b), RGB(r, g, b));
	}
}

void Board::display_playerInfo(Player** pls,int size, int x, int y)
{
	char fp[30] = "Player: ";
	char money[30] = "Cash: "; string mon = to_string(pls[0]->getMoney());
	strcat(fp, pls[0]->getName());
	strcat(money, mon.c_str()); money[14] = '\0';
	
	colour pl1 = pls[0]->getcolour();

	myDrawText(x + 160, y + 298, 20, fp, RGB(pl1.r, pl1.g, pl1.b), RGB(255, 255, 255));
	myDrawText(x + 160, y + 318, 20, money, RGB(pl1.r, pl1.g, pl1.b), RGB(255, 255, 255));
	myDrawText(x + 160, y + 338, 20, "Properties:", RGB(pl1.r, pl1.g, pl1.b), RGB(255, 255, 255));
	for (int i = 0; i < pls[0]->getPropertySize(); i++)
	{
		myDrawText(x + 170, y + 358 + (i * 20), 20, pls[0]->PropertyName(i), RGB(pl1.r, pl1.g, pl1.b), RGB(255, 255, 255));
	}
	
	if (size > 1)
	{
		char sp[30] = "Player: ";
		char money1[30] = "Cash: "; string mon1 = to_string(pls[1]->getMoney());
		strcat(sp, pls[1]->getName());
		strcat(money1, mon1.c_str()); money1[14] = '\0';
		pl1 = pls[1]->getcolour();

		myDrawText(x + 662, y + 120, 20, sp, RGB(pl1.r, pl1.g, pl1.b), RGB(255, 255, 255));
		myDrawText(x + 662, y + 140, 20, money1, RGB(pl1.r, pl1.g, pl1.b), RGB(255, 255, 255));
		myDrawText(x + 662, y + 160, 20, "Properties:", RGB(pl1.r, pl1.g, pl1.b), RGB(255, 255, 255));
		for (int i = 0; i < pls[1]->getPropertySize(); i++)
		{
			myDrawText(x + 672, y + 180 + (i * 20), 20, pls[1]->PropertyName(i), RGB(pl1.r, pl1.g, pl1.b), RGB(255, 255, 255));
		}
	}
}

void Board::display_Board(int x, int y)
{
	//myRect(x, y, x + 1000, y + 670, RGB(42, 6, 6), RGB(255, 255, 230));
	//myRect(120 + x, y + 90, x + 880, y + 580, RGB(42, 6, 6), RGB(42, 6, 6));
	//myLine(x, y + 90, x + 1000, y + 90, RGB(0, 0, 0));
	//myLine(x, y + 580, x + 1000, y + 580, RGB(0, 0, 0));
	//myLine(x + 120, y, x + 120, y + 670, RGB(0, 0, 0));
	//myLine(x + 880, y, x + 880, y + 670, RGB(0, 0, 0));
	//int px = 204 + x;
	//for (int i = 0; i < 8; i++)
	//{
	//	myLine(px, y, px, y + 90, RGB(0, 0, 0));
	//	px += 84;
	//}
	//px = 204 + x;
	//for (int i = 0; i < 8; i++)
	//{
	//	myLine(px, y + 580, px, y + 670, RGB(0, 0, 0));
	//	px += 84;
	//}
	//int py = y + 144;
	//for (int i = 0; i < 8; i++)
	//{
	//	myLine(x + 880, py, x + 1000, py, RGB(0, 0, 0));
	//	py += 54;
	//}
	//py = y + 144;
	//for (int i = 0; i < 8; i++)
	//{
	//	myLine(x, py, x + 120, py, RGB(0, 0, 0));
	//	py += 54;
	//}
	//myRect(x + 360, y + 298, x + 632, y + 385, RGB(0, 0, 0), RGB(199, 0, 0));
	//myDrawTextWithFont(x + 365, y + 300, 80, "Monopoly", RGB(255, 255, 255), RGB(199, 0, 0));
	//myRect(x + 150, y + 145, x + 340, y + 260, RGB(0, 0, 0), RGB(92, 142, 224));
	//myDrawText(x + 175, y + 195, 30, "COMMUNITY CHEST", RGB(255, 255, 255), RGB(92, 142, 224));
	//myRect(x + 660, y + 410, x + 850, y + 525, RGB(0, 0, 0), RGB(214, 62, 62));
	//myDrawText(x + 725, y + 460, 30, "CHANCE ?", RGB(255, 255, 255), RGB(214, 62, 62));
	//myDrawText(x + 36, y + 30, 30, "START", RGB(0, 0, 0), RGB(255, 255, 230));
	//myDrawText(x + 126, y + 10, 30, "Iqbal Town\n       A", RGB(153, 51, 51), RGB(255, 255, 230));
	//myRect(x + 122, y + 70, x + 203, y + 89, RGB(153, 51, 51), RGB(153, 51, 51));
	//myRect(x + 206, y+2, x + 287, y + 89, RGB(92, 142, 224), RGB(92, 142, 224));
	//myDrawText(x + 210, y + 10, 30, "Community\n    Chest", RGB(255, 255, 255), RGB(92, 142, 224));
	//myDrawText(x + 294, y + 10, 30, "Iqbal Town\n       B", RGB(153, 51, 51), RGB(255, 255, 230));
	//myRect(x + 290, y + 70, x + 371, y + 89, RGB(153, 51, 51), RGB(153, 51, 51));
	//myDrawText(x + 385, y + 10, 30, "Land Tax", RGB(0, 0, 0), RGB(255, 255, 230));
	//myRect(x + 458, y, x + 539, y + 89, RGB(0, 0, 0), RGB(0, 0, 0));
	//myDrawText(x + 472, y + 10, 30, " Metro\nStation", RGB(255, 255, 255), RGB(0, 0, 0));
	//myDrawText(x + 556, y + 10, 30, "Kareem\n Block", RGB(153, 51, 51), RGB(255, 255, 230));
	//myRect(x + 542, y + 70, x + 623, y + 89, RGB(153, 51, 51), RGB(153, 51, 51));
	//myRect(x + 626, y+2, x + 707, y + 89, RGB(214, 62, 62), RGB(214, 62, 62));
	//myDrawText(x + 640, y + 10, 30, "Chance", RGB(255, 255, 255), RGB(214, 62, 62));
	//myDrawText(x + 714, y + 10, 30, "Johar Town\n       A", RGB(0, 204, 204), RGB(255, 255, 230));
	//myRect(x + 710, y + 70, x + 791, y + 89, RGB(0, 204, 204), RGB(0, 204, 204));
	//myDrawText(x + 798, y + 10, 30, "Johar Town\n       B", RGB(0, 204, 204), RGB(255, 255, 230));
	//myRect(x + 794, y + 70, x + 879, y + 89, RGB(0, 204, 204), RGB(0, 204, 204));
	//myDrawText(x + 922, y + 30, 30, "JAIL", RGB(0, 0, 0), RGB(255, 255, 230));
	//myDrawText(x + 906, y + 95, 30, "Faisal Town\n      A", RGB(255, 102, 153), RGB(255, 255, 230));
	//myRect(x + 882, y + 92, x + 900, y + 143, RGB(255, 102, 153), RGB(255, 102, 153));
	//myRect(x + 882, y + 146, x + 999, y + 197, RGB(87, 89, 93), RGB(87, 89, 93));
	//myDrawText(x + 910, y + 159, 30, "WASA", RGB(255, 255, 255), RGB(87, 89, 93));
	//myDrawText(x + 906, y + 203, 30, "Faisal Town\n      B", RGB(255, 102, 153), RGB(255, 255, 230));
	//myRect(x + 882, y + 200, x + 900, y + 251, RGB(255, 102, 153), RGB(255, 102, 153));
	//myRect(x + 882, y + 254, x + 999, y + 305, RGB(87, 89, 93), RGB(87, 89, 93));
	//myDrawText(x + 910, y + 267, 30, "PTCL", RGB(255, 255, 255), RGB(87, 89, 93));
	//myRect(x + 882, y + 308, x + 1000, y + 359, RGB(0, 0, 0), RGB(0, 0, 0));
	//myDrawText(x + 906, y + 318, 30, "    Bus\n Station", RGB(255, 255, 255), RGB(0, 0, 0));
	//myDrawText(x + 906, y + 365, 30, "Faisal Town\n      C", RGB(255, 102, 153), RGB(255, 255, 230));
	//myRect(x + 882, y + 362, x + 900, y + 413, RGB(255, 102, 153), RGB(255, 102, 153));
	//myRect(x + 882, y + 416, x + 999, y + 467, RGB(92, 142, 224), RGB(92, 142, 224));
	//myDrawText(x + 906, y + 419, 30, "Community\n    Chest", RGB(255, 255, 255), RGB(92, 142, 224));
	//myDrawText(x + 906, y + 473, 30, "Model Town\n      A", RGB(255, 209, 26), RGB(255, 255, 230));
	//myRect(x + 882, y + 470, x + 900, y + 521, RGB(255, 209, 26), RGB(255, 209, 26));
	//myDrawText(x + 906, y + 527, 30, "Model Town\n      B", RGB(255, 209, 26), RGB(255, 255, 230));
	//myRect(x + 882, y + 524, x + 900, y + 579, RGB(255, 209, 26), RGB(255, 209, 26));
	//myDrawText(x + 906, y + 616, 30, "PARKING", RGB(0, 0, 0), RGB(255, 255, 230));
	//myDrawText(x + 8, y + 616, 30, "GO TO PRISON", RGB(0, 0, 0), RGB(255, 255, 230));
	//myDrawText(x + 140, y + 617, 30, "DHA A", RGB(255, 255, 0), RGB(255, 255, 230));
	//myRect(x + 122, y + 582, x + 203, y + 602, RGB(255, 255, 0), RGB(255, 255, 0));
	//myRect(x + 206, y + 582, x + 287, y + 669, RGB(87, 89, 93), RGB(87, 89, 93));
	//myDrawText(x + 225, y + 617, 30, "LESCO", RGB(255, 255, 230), RGB(87, 89, 93));
	//myDrawText(x + 310, y + 617, 30, "Liberty", RGB(224, 102, 255), RGB(255, 255, 230));
	//myRect(x + 290, y + 582, x + 371, y + 602, RGB(224, 102, 255), RGB(224, 102, 255));
	//myDrawText(x + 382, y + 617, 30, "Gulberg B", RGB(224, 102, 255), RGB(255, 255, 230));
	//myRect(x + 374, y + 582, x + 455, y + 602, RGB(224, 102, 255), RGB(224, 102, 255));
	//myRect(x + 458, y + 582, x + 539, y + 670, RGB(0, 0, 0), RGB(0, 0, 0));
	//myDrawText(x + 474, y + 607, 30, "Railway\n Station", RGB(255, 255, 255), RGB(0, 0, 0));
	//myRect(x + 542, y + 582, x + 623, y + 669, RGB(87, 89, 93), RGB(87, 89, 93));
	//myDrawText(x + 572, y + 617, 30, "SUI", RGB(255, 255, 255), RGB(87, 89, 93));
	//myDrawText(x + 632, y + 617, 30, "Gulberg A", RGB(224, 102, 255), RGB(255, 255, 230));
	//myRect(x + 626, y + 582, x + 707, y + 602, RGB(224, 102, 255), RGB(224, 102, 255));
	//myRect(x + 710, y + 582, x + 791, y + 669, RGB(214, 62, 62), RGB(214, 62, 62));
	//myDrawText(x + 724, y + 617, 30, "Chance", RGB(255, 255, 255), RGB(214, 62, 62));
	//myDrawText(x + 802, y + 617, 30, "Link Road", RGB(255, 209, 26), RGB(255, 255, 230));
	//myRect(x + 794, y + 582, x + 879, y + 602, RGB(255, 209, 26), RGB(255, 209, 26));
	//myDrawText(x + 3, y + 95, 30, "Bahria Town\n      C", RGB(0, 51, 204), RGB(255, 255, 230));
	//myRect(x + 119, y + 92, x + 96, y + 143, RGB(0, 51, 204), RGB(0, 51, 204));
	//myDrawText(x + 12, y + 159, 30, "Property Tax", RGB(0, 0, 0), RGB(255, 255, 230));
	//myDrawText(x + 3, y + 203, 30, "Bahria Town\n      B", RGB(0, 51, 204), RGB(255, 255, 230));
	//myRect(x + 119, y + 200, x + 96, y + 251, RGB(0, 51, 204), RGB(0, 51, 204));
	//myRect(x + 119, y + 254, x+1, y + 305, RGB(214, 62, 62), RGB(214, 62, 62));
	//myDrawText(x + 28, y + 267, 30, "Chance", RGB(255, 255, 255), RGB(214, 62, 62));
	//myRect(x + 119, y + 308, x, y + 359, RGB(0, 0, 0), RGB(0, 0, 0));
	//myDrawText(x + 17, y + 318, 30, "Orange Train", RGB(255, 255, 255), RGB(0, 0, 0));
	//myDrawText(x + 3, y + 365, 30, "Bahria Town\n      A", RGB(0, 51, 204), RGB(255, 255, 230));
	//myRect(x + 119, y + 362, x + 96, y + 413, RGB(0, 51, 204), RGB(0, 51, 204));
	//myRect(x + 119, y + 416, x+1, y + 467, RGB(92, 142, 224), RGB(92, 142, 224));
	//myDrawText(x + 17, y + 419, 30, "Community\n    Chest", RGB(255, 255, 255), RGB(92, 142, 224));
	//myDrawText(x + 20, y + 485, 30, "Y Block", RGB(255, 255, 0), RGB(255, 255, 230));
	//myRect(x + 119, y + 470, x + 96, y + 521, RGB(255, 255, 0), RGB(255, 255, 0));
	//myDrawText(x + 25, y + 537, 30, "DHA B", RGB(255, 255, 0), RGB(255, 255, 230));
	//myRect(x + 119, y + 524, x + 96, y + 579, RGB(255, 255, 0), RGB(255, 255, 0));
	myRect(x, y, x + 1000, y + 670, RGB(0,0,0), RGB(255,255,255));
	myLine(x, y + 90, x + 1000, y + 90, RGB(0, 0, 0));
	myLine(x, y + 580, x + 1000, y + 580, RGB(0, 0, 0));
	myLine(x + 120, y, x + 120, y + 670, RGB(0, 0, 0));
	myLine(x + 880, y, x + 880, y + 670, RGB(0, 0, 0));
	int px = 204 + x;
	for (int i = 0; i < 8; i++)
	{
		myLine(px, y, px, y + 90, RGB(0, 0, 0));
		px += 84;
	}
	px = 204 + x;
	for (int i = 0; i < 8; i++)
	{
		myLine(px, y + 580, px, y + 670, RGB(0, 0, 0));
		px += 84;
	}
	int py = y + 144;
	for (int i = 0; i < 8; i++)
	{
		myLine(x + 880, py, x + 1000, py, RGB(0, 0, 0));
		py += 54;
	}
	py = y + 144;
	for (int i = 0; i < 8; i++)
	{
		myLine(x, py, x + 120, py, RGB(0, 0, 0));
		py += 54;
	}
	myRect(x + 360, y + 298, x + 632, y + 385, RGB(0, 0, 0), RGB(199, 0, 0));
	myDrawTextWithFont(x + 365, y + 300, 80, "Monopoly", RGB(255, 255, 255), RGB(199, 0, 0));
	myRect(x + 150, y + 145, x + 340, y + 260, RGB(255, 255, 255), RGB(92, 142, 224));
	myDrawText(x + 175, y + 195, 30, "COMMUNITY CHEST", RGB(255, 255, 255), RGB(92, 142, 224));
	myRect(x + 660, y + 410, x + 850, y + 525, RGB(255, 255, 255), RGB(214, 62, 62));
	myDrawText(x + 725, y + 460, 30, "CHANCE ?", RGB(255, 255, 255), RGB(214, 62, 62));
	myDrawText(x + 36, y + 30, 30, "START", RGB(0, 0, 0), RGB(255, 255, 255));
	myDrawText(x + 126, y + 10, 30, "Iqbal Town\n       A", RGB(153, 51, 51), RGB(255, 255, 255));
	myRect(x + 122, y + 70, x + 203, y + 89, RGB(153, 51, 51), RGB(153, 51, 51));
	myRect(x + 206, y + 2, x + 287, y + 89, RGB(92, 142, 224), RGB(92, 142, 224));
	myDrawText(x + 210, y + 10, 30, "Community\n    Chest", RGB(255, 255, 255),RGB(92, 142, 224));
	myDrawText(x + 294, y + 10, 30, "Iqbal Town\n       B", RGB(153, 51, 51), RGB(255, 255, 255));
	myRect(x + 290, y + 70, x + 371, y + 89, RGB(153, 51, 51), RGB(153, 51, 51));
	myDrawText(x + 385, y + 10, 30, "Land Tax", RGB(0, 0, 0), RGB(255, 255, 255));
	myRect(x + 458, y, x + 539, y + 89, RGB(0, 0, 0), RGB(0, 0, 0));
	myDrawText(x + 472, y + 10, 30, " Metro\nStation", RGB(255, 255, 255), RGB(0, 0, 0));
	myDrawText(x + 556, y + 10, 30, "Kareem\n Block", RGB(153, 51, 51), RGB(255, 255, 255));
	myRect(x + 542, y + 70, x + 623, y + 89, RGB(153, 51, 51), RGB(153, 51, 51));
	myRect(x + 626, y + 2, x + 707, y + 89, RGB(214, 62, 62), RGB(214, 62, 62));
	myDrawText(x + 640, y + 10, 30, "Chance", RGB(255, 255, 255), RGB(214, 62, 62));
	myDrawText(x + 714, y + 10, 30, "Johar Town\n       A", RGB(0, 204, 204), RGB(255, 255, 255));
	myRect(x + 710, y + 70, x + 791, y + 89, RGB(0, 204, 204), RGB(0, 204, 204));
	myDrawText(x + 798, y + 10, 30, "Johar Town\n       B", RGB(0, 204, 204), RGB(255, 255, 255));
	myRect(x + 794, y + 70, x + 879, y + 89, RGB(0, 204, 204), RGB(0, 204, 204));
	myDrawText(x + 922, y + 30, 30, "JAIL", RGB(0, 0, 0), RGB(255, 255, 255));
	myDrawText(x + 906, y + 95, 30, "Faisal Town\n      A", RGB(255, 102, 153), RGB(255, 255, 255));
	myRect(x + 882, y + 92, x + 900, y + 143, RGB(255, 102, 153), RGB(255, 102, 153));
	myRect(x + 882, y + 146, x + 999, y + 197, RGB(87, 89, 93), RGB(87, 89, 93));
	myDrawText(x + 910, y + 159, 30, "WASA", RGB(255, 255, 255),RGB(87, 89, 93));
	myDrawText(x + 906, y + 203, 30, "Faisal Town\n      B", RGB(255, 102, 153), RGB(255, 255, 255));
	myRect(x + 882, y + 200, x + 900, y + 251, RGB(255, 102, 153), RGB(255, 102, 153));
	myRect(x + 882, y + 254, x + 999, y + 305, RGB(87, 89, 93), RGB(87, 89, 93));
	myDrawText(x + 910, y + 267, 30, "PTCL", RGB(255, 255, 255), RGB(87, 89, 93));
	myRect(x + 882, y + 308, x + 1000, y + 359, RGB(0, 0, 0), RGB(0, 0, 0));
	myDrawText(x + 906, y + 318, 30, "    Bus\n Station", RGB(255, 255, 255),RGB(0, 0, 0));
	myDrawText(x + 906, y + 365, 30, "Faisal Town\n      C", RGB(255, 102, 153), RGB(255, 255, 255));
	myRect(x + 882, y + 362, x + 900, y + 413, RGB(255, 102, 153), RGB(255, 102, 153));
	myRect(x + 882, y + 416, x + 999, y + 467, RGB(92, 142, 224), RGB(92, 142, 224));
	myDrawText(x + 906, y + 419, 30, "Community\n    Chest", RGB(255, 255, 255), RGB(92, 142, 224));
	myDrawText(x + 906, y + 473, 30, "Model Town\n      A", RGB(255, 209, 26), RGB(255, 255, 255));
	myRect(x + 882, y + 470, x + 900, y + 521, RGB(255, 209, 26), RGB(255, 209, 26));
	myDrawText(x + 906, y + 527, 30, "Model Town\n      B", RGB(255, 209, 26), RGB(255, 255, 255));
	myRect(x + 882, y + 524, x + 900, y + 579, RGB(255, 209, 26), RGB(255, 209, 26));
	myDrawText(x + 906, y + 616, 30, "PARKING", RGB(0, 0, 0), RGB(255, 255, 255));
	myDrawText(x + 8, y + 616, 30, "GO TO PRISON", RGB(0, 0, 0), RGB(255, 255, 255));
	myDrawText(x + 140, y + 617, 30, "DHA A", RGB(255, 255, 0), RGB(255, 255, 255));
	myRect(x + 122, y + 582, x + 203, y + 602, RGB(255, 255, 0), RGB(255, 255, 0));
	myRect(x + 206, y + 582, x + 287, y + 669, RGB(87, 89, 93), RGB(87, 89, 93));
	myDrawText(x + 225, y + 617, 30, "LESCO", RGB(255, 255, 255),RGB(87, 89, 93));
	myDrawText(x + 310, y + 617, 30, "Liberty", RGB(224, 102, 255), RGB(255, 255, 255));
	myRect(x + 290, y + 582, x + 371, y + 602, RGB(224, 102, 255), RGB(224, 102, 255));
	myDrawText(x + 382, y + 617, 30, "Gulberg B", RGB(224, 102, 255), RGB(255, 255, 255));
	myRect(x + 374, y + 582, x + 455, y + 602, RGB(224, 102, 255), RGB(224, 102, 255));
	myRect(x + 458, y + 582, x + 539, y + 670, RGB(0, 0, 0), RGB(0, 0, 0));
	myDrawText(x + 474, y + 607, 30, "Railway\n Station", RGB(255, 255, 255),RGB(0, 0, 0));
	myRect(x + 542, y + 582, x + 623, y + 669, RGB(87, 89, 93), RGB(87, 89, 93));
	myDrawText(x + 572, y + 617, 30, "SUI", RGB(255, 255, 255),RGB(87, 89, 93));
	myDrawText(x + 632, y + 617, 30, "Gulberg A", RGB(224, 102, 255), RGB(255, 255, 255));
	myRect(x + 626, y + 582, x + 707, y + 602, RGB(224, 102, 255), RGB(224, 102, 255));
	myRect(x + 710, y + 582, x + 791, y + 669, RGB(214, 62, 62), RGB(214, 62, 62));
	myDrawText(x + 724, y + 617, 30, "Chance", RGB(255, 255, 255),RGB(214, 62, 62));
	myDrawText(x + 802, y + 617, 30, "Link Road", RGB(255, 209, 26), RGB(255, 255, 255));
	myRect(x + 794, y + 582, x + 879, y + 602, RGB(255, 209, 26), RGB(255, 209, 26));
	myDrawText(x + 3, y + 95, 30, "Bahria Town\n      C", RGB(0, 51, 204), RGB(255, 255, 255));
	myRect(x + 119, y + 92, x + 96, y + 143, RGB(0, 51, 204), RGB(0, 51, 204));
	myDrawText(x + 12, y + 159, 30, "Property Tax", RGB(0, 0, 0), RGB(255, 255, 255));
	myDrawText(x + 3, y + 203, 30, "Bahria Town\n      B", RGB(0, 51, 204), RGB(255, 255, 255));
	myRect(x + 119, y + 200, x + 96, y + 251, RGB(0, 51, 204), RGB(0, 51, 204));
	myRect(x + 119, y + 254, x + 1, y + 305, RGB(214, 62, 62), RGB(214, 62, 62));
	myDrawText(x + 28, y + 267, 30, "Chance", RGB(255, 255, 255),RGB(214, 62, 62));
	myRect(x + 119, y + 308, x, y + 359, RGB(0, 0, 0), RGB(0, 0, 0));
	myDrawText(x + 17, y + 318, 30, "Orange Train", RGB(255, 255, 255),RGB(0, 0, 0));
	myDrawText(x + 3, y + 365, 30, "Bahria Town\n      A", RGB(0, 51, 204), RGB(255, 255, 255));
	myRect(x + 119, y + 362, x + 96, y + 413, RGB(0, 51, 204), RGB(0, 51, 204));
	myRect(x + 119, y + 416, x + 1, y + 467, RGB(92, 142, 224), RGB(92, 142, 224));
	myDrawText(x + 17, y + 419, 30, "Community\n    Chest", RGB(255, 255, 255),RGB(92, 142, 224));
	myDrawText(x + 20, y + 485, 30, "Y Block", RGB(255, 255, 0), RGB(255, 255, 255));
	myRect(x + 119, y + 470, x + 96, y + 521, RGB(255, 255, 0), RGB(255, 255, 0));
	myDrawText(x + 25, y + 537, 30, "DHA B", RGB(255, 255, 0), RGB(255, 255, 255));
	myRect(x + 119, y + 524, x + 96, y + 579, RGB(255, 255, 0), RGB(255, 255, 0));
}

void Board::playerOnPropertyTax()
{
	float tax=players[turn]->calculatePropertyTax();
	char option;
	bool bankrupt = players[turn]->checkBankrupt(tax);
	if (bankrupt == true)
	{
		bankruptToBank();
	}
	else
	{
	d:
		system("cls"); reprint();
		cout << players[turn]->getName() << ": " << endl;
		cout << "Cash: " << players[turn]->getMoney() << endl;
		cout << "Property Tax: " << tax << endl;
		cout << endl;
		cout << "P) Pay Property Tax" << endl;
		cout << "M) Mortgage Property"<<endl;
		cout << "S) Sell Property" << endl;
		cin >> option;
		if (option == 'p' || option == 'P')
		{
			if (players[turn]->getMoney() >= tax)
			{
				players[turn]->deductMoney(tax);
				reprint();
			}
			else
			{
				cout << "You do not have enough money!" << endl;
				pause();
				goto d;
			}
		}
		else if (option == 'm' || option == 'M')
		{
			players[turn]->mortgageProperty();
			reprint();
			goto d;
		}
		else if (option == 's' || option == 'S')
		{
			players[turn]->sell(players, playerSize);
			reprint();
			goto d;
		}
		else
		{
			cout << "Invalid option!" << endl;
			goto d;
		}
	}
}

bool Board::checkOwnershipOfGroup(Property* p)
{
	char* group = p->getGroup();
	Player* owner = p->getOwner();
	for (int x = 0; x < 28; x++)
	{
		if (!strcmp(properties[x]->getGroup(), group))
		{
			if (properties[x]->getOwner() == nullptr)
			{
				return false;
			}
			if (properties[x]->getOwner()!=owner)
			{
				return false;
			}
		}
	}
	return true;
}

bool Board::checkHousesInGroup(Property*p)
{
	char* group = p->getGroup();
	int houses = dynamic_cast<UpgradableProperty*>(p)->getHouse();
	houses += dynamic_cast<UpgradableProperty*>(p)->getShop() * 3;
	houses += dynamic_cast<UpgradableProperty*>(p)->getShop() * 10;
	int house1 = 0;
	for (int x = 0; x < 28; x++)
	{
		house1 = 0;
		if (!strcmp(properties[x]->getGroup(), group))
		{
			house1 = dynamic_cast<UpgradableProperty*>(properties[x])->getHouse();
			house1 += dynamic_cast<UpgradableProperty*>(properties[x])->getShop()*3;
			house1 += dynamic_cast<UpgradableProperty*>(properties[x])->getHotel()*10;
			if (house1 < houses)
			{
				return false;
			}
		}
	}
	return true;
}

bool Board::checkHousesForShop(Property* p)
{
	char* group = p->getGroup();
	int houses = dynamic_cast<UpgradableProperty*>(p)->getHouse();
	int shop = dynamic_cast<UpgradableProperty*>(p)->getShop();
	int shop1;
	if (houses < 3)
	{
		return false;
	}
	for (int x = 0; x < 28; x++)
	{
		houses = 0;
		shop1 = 0;
		if (!strcmp(properties[x]->getGroup(), group))
		{
			houses = dynamic_cast<UpgradableProperty*>(properties[x])->getHouse();
			shop1 = dynamic_cast<UpgradableProperty*>(properties[x])->getShop();
			if (houses<3 && shop1<=shop)
			{
				return false;
			}
		}
	}
	return true;
}

bool Board::checkShopsInGroup(Property* p)
{
	char* group = p->getGroup();
	int shops = dynamic_cast<UpgradableProperty*>(p)->getShop();
	shops += dynamic_cast<UpgradableProperty*>(p)->getHotel() * 2;
	int shop1=0;
	for (int x = 0; x < 28; x++)
	{
		shop1 = 0;
		if (!strcmp(properties[x]->getGroup(),group))
		{
			shop1 += dynamic_cast<UpgradableProperty*>(properties[x])->getShop();
			shop1 += dynamic_cast<UpgradableProperty*>(properties[x])->getHotel() * 2;
			if (shop1 < shops)
			{
				return false;
			}
		}
	}
	return true;
}

bool Board::checkHotelsInGroup(Property* p)
{
	char* group = p->getGroup();
	int hotels = dynamic_cast<UpgradableProperty*>(p)->getHotel();
	int hotel1 = 0;
	for (int x = 0; x < 28; x++)
	{
		hotel1 = 0;
		if (!strcmp(properties[x]->getGroup(), group))
		{
			hotel1 = dynamic_cast<UpgradableProperty*>(properties[x])->getHotel();
			if (hotel1 < hotels)
			{
				return false;
			}
		}
	}
	return true;
}

bool Board::checkRequirementsForHotel(Property* p)
{
	char* group = p->getGroup();
	int houses = dynamic_cast<UpgradableProperty*>(p)->getHouse();
	int shop = dynamic_cast<UpgradableProperty*>(p)->getShop();
	int hotel = dynamic_cast<UpgradableProperty*>(p)->getHotel();
	int hotel1 = 0;
	if (houses < 4 || shop< 2)
	{
		return false;
	}
	for (int x = 0; x < 28; x++)
	{
		houses = 0;
		shop = 0;
		hotel1 = 0;
		if (!strcmp(properties[x]->getGroup(),group))
		{
			houses = dynamic_cast<UpgradableProperty*>(properties[x])->getHouse();
			shop = dynamic_cast<UpgradableProperty*>(properties[x])->getShop();
			hotel1 = dynamic_cast<UpgradableProperty*>(properties[x])->getHotel();
			if ((houses<4 || shop<2) && hotel1 <= hotel)
			{
				return false;
			}
		}
	}
	return true;
}

Board::~Board()
{
	for (int x = 0; x < playerSize; x++)
	{
		delete players[x];
	}
	delete[] players;
	for (int x = 0; x < 28; x++)
	{
		delete properties[x];
	}
	delete[] properties;
}

void Board::playerOnCommunityChest()
{
	system("cls"); reprint();
	//reprint();
	char option='\0';
	bool st;
	float charges;
	instruction i = communityChest.returnInstruction();
	cout << players[turn]->getName() << ":"<<endl;
	cout << "Community Chest: " << endl;
	cout << i.getText() << endl;
	pause();
	switch (i.getId())
	{
	case 0:
		players[turn]->setPosition(0);
		players[turn]->addMoney(400);
		reprint();
		cout << players[turn]->getName() << " collected 400!" << endl;
		pause();
		break;
	case 1:
		players[turn]->addMoney(200);
		reprint();
		cout << players[turn]->getName() << " recieved 200 from bank" << endl;
		pause();
		break;
	case 2:
		st=payMenu(200);
		if (st)
		{
			cout << players[turn]->getName() << " paid 200 to doctor" << endl;
			reprint();
			pause();
		}
		break;
	case 3:
		players[turn]->addMoney(50);
		cout << players[turn]->getName() << " recieved 50 from sale" << endl;
		reprint();
		pause();
		break;
	case 4:
		players[turn]->setJailcard(true);
		cout << players[turn]->getName() << " recieved jail card" << endl;
		reprint();
		pause();
		break;
	case 5:
		players[turn]->addMoney(150);
		cout << players[turn]->getName() << " collected 150 from income tax refund" << endl;
		reprint();
		pause();
		break;
	case 6:
		players[turn]->addMoney(200);
		cout << players[turn]->getName() << " recieved 200 from health insurance" << endl;
		reprint();
		pause();
		break;
	case 7:
		st=payMenu(100);
		if (st)
		{
			cout << players[turn]->getName() << " paid 100 as donation to hospital" << endl;
			reprint();
			pause();
		}
		break;
	case 8:
		st=payMenu(200);
		if (st)
		{
			cout << players[turn]->getName() << " paid 200 as student tax" << endl;
			reprint();
			pause();
		}
		break;
	case 9:
		players[turn]->addMoney(50);
		cout << players[turn]->getName() << " recieved 50 for his services" << endl;
		reprint();
		pause();
		break;
	case 10:
		charges = players[turn]->calculateStreetRepairCharges(50,125);
		st = payMenu(charges);
		if (st)
		{
			cout << players[turn]->getName() << " paid "<<charges<<" as street repair charges" << endl;
			reprint();
			pause();
		}
		break;
	case 11:
		players[turn]->addMoney(300);
		cout << players[turn]->getName() << " recieved 300 as pize money!" << endl;
		reprint();
		pause();
		break;
	case 12:
		st = payMenu(50);
		if (st)
		{
			cout << players[turn]->getName() << " paid 50 water bill" << endl;
			reprint();
			pause();
		}
		break;
	case 13:
		st = payMenu(80);
		if (st)
		{
			cout << players[turn]->getName() << " paid 80 as electricity bill" << endl;
			reprint();
			pause();
		}
		break;
	case 14:
		st = payMenu(50);
		if (st)
		{
			cout << players[turn]->getName() << " paid 50 as internet bill" << endl;
			reprint();
			pause();
		}
		break;
	}
}

void Board::playerOnChance()
{
	system("cls"); reprint();
	char option='\0';
	bool st;
	int pos;
	float charges;
	Property* temp;
	instruction i = chance.returnInstruction();
	cout << players[turn]->getName() << ":" << endl;
	cout << "Chance: " << endl;
	cout << i.getText() << endl;
	pause();
	switch (i.getId())
	{
	case 0:
		players[turn]->setPosition(0);
		players[turn]->addMoney(300);
		reprint();
		cout << players[turn]->getName() << " collected 300!" << endl;
		pause();
		break;
	case 1:
		players[turn]->setPosition(29);
		reprint();
		playerOnProperty(29);
		pause();
		break;
	case 2:
		temp = findNearestUtility();
		if (temp->getOwner() == nullptr)
		{
			st=payMenu(temp->getcost());
			if (st)
			{
				players[turn]->AddProperty(temp);
				cout << "Property purchased!" << endl;
				reprint();
				pause();
			}
		}
		else
		{
			st = payMenu(dice * 5.0);
			if (st)
			{
				temp->getOwner()->addMoney(dice * 5.0);
				reprint();
			}
		}
		break;
	case 3:
		temp = findNearestStation();
		if (temp->getOwner() == nullptr)
		{
			st = payMenu(temp->getcost());
			if (st)
			{
				players[turn]->AddProperty(temp);
				cout << "Property purchased!" << endl;
				reprint();
				pause();
			}
		}
		else
		{
			st = payMenu(temp->getrent()*2);
			if (st)
			{
				temp->getOwner()->addMoney(temp->getrent()*2);
				reprint();
			}
		}
		break;
	case 4:
		temp = findNearestStation();
		if (temp->getOwner() == nullptr)
		{
			st = payMenu(temp->getcost());
			if (st)
			{
				players[turn]->AddProperty(temp);
				cout << "Property purchased!" << endl;
				reprint();
				pause();
			}
		}
		else
		{
			st = payMenu(temp->getrent() * 2);
			if (st)
			{
				temp->getOwner()->addMoney(temp->getrent() * 2);
				reprint();
			}
		}
		break;
	case 5:
		pos = players[turn]->getPosition();
		players[turn]->setPosition(18);
		reprint();
		if (pos > 18)
		{
			players[turn]->addMoney(300);
			cout << players[turn]->getName() << " collected 300!" << endl;
			reprint();
			pause();
		}
		playerOnProperty(18);
		break;
	case 6:
		players[turn]->addMoney(100);
		cout << players[turn]->getName() << " recieved 100 from bank" << endl;
		reprint();
		pause();
		break;
	case 7:
		players[turn]->setJailcard(true);
		cout << players[turn]->getName() << " recieved jail card!" << endl;
		reprint();
		pause();
		break;
	case 8:
		pos = players[turn]->getPosition();
		players[turn]->setPosition(pos - 4);
		reprint();
		playerOnProperty(pos-4);
		break;
	case 9:
		charges = players[turn]->calculateStreetRepairCharges(50,100);
		st = payMenu(charges);
		if (st)
		{
			cout << players[turn]->getName() << " paid " << charges << " to repair property!" << endl;
			reprint();
			pause();
		}
		break;
	case 10:
		st = payMenu(25);
		if (st)
		{
			cout << players[st]->getName() << " paid 25 as tax" << endl;
			reprint();
			pause();
		}
		break;
	case 11:
		st = payMenu((playerSize-1) * 25.0);
		if (st)
		{
			for (int x = 0; x < playerSize; x++)
			{
				if (x != turn)
				{
					players[x]->addMoney(25);
					cout << players[x]->getName() << " recieved 25!" << endl;
					reprint();
					pause();
				}
			}
		}
		break;
	case 12:
		players[turn]->addMoney(150);
		cout << players[turn]->getName() << " recieved 150 from bank" << endl;
		reprint();
		pause();
		break;
	case 13:
		players[turn]->setPosition(4);
		reprint();
		players[turn]->addMoney(500);
		cout << players[turn]->getName() << " collected 500!" << endl;
		reprint();
		break;
	case 14:
		players[turn]->setPosition(5);
		reprint();
		players[turn]->addMoney(500);
		cout << players[turn]->getName() << " collected 500!" << endl;
		reprint();
		pause();
		playerOnProperty(5);
		break;
	}
}

bool Board::payMenu(float x)
{
	bool bankrupt = players[turn]->checkBankrupt(x);
	if (bankrupt)
	{
		bankruptToBank();
		return false;
	}
	else
	{
		a:
		char option;
		cout << "P) Pay "<<x << endl;
		cout << "M) Mortgage Property" << endl;
		cout << "S) Sell Property" << endl;
		if (players[turn]->getJailCard())
		{
			cout << "J) Sell Jail Card!" << endl;
		}
		cin >> option;
		if (option == 'p' && players[turn]->getMoney() >= x)
		{
			if (players[turn]->getMoney() >= x)
			{
				players[turn]->deductMoney(x);
				reprint();
			}
			else
			{
				cout << "You dont have enough money" << endl;
				goto a;
			}
		}
		else if (option == 'm' || option == 'M')
		{
			players[turn]->mortgageProperty();
			reprint();
			goto a;
		}
		else if (option == 's' || option == 'S')
		{
			players[turn]->sell(players, playerSize);
			reprint();
			goto a;
		}
		else if ((option == 'j' || option == 'J') && players[turn]->getJailCard())
		{
			players[turn]->setJailcard(false);
			players[turn]->addMoney(400);
			reprint();
			goto a;
		}
	}
	return true;
}

Property* Board::findNearestUtility()
{
	int pos = players[turn]->getPosition();
	if (pos == 7)
	{
		players[turn]->setPosition(12);
		reprint();
		return findProperty(12);
	}
	else if (pos == 22)
	{
		players[turn]->setPosition(24);
		reprint();
		return findProperty(24);
	}
	else if (pos==36)
	{
		players[turn]->setPosition(12);
		reprint();
		players[turn]->addMoney(500);
		cout << players[turn]->getName() << " colected 500!" << endl;
		pause();
		return findProperty(12);
	}
}

Property* Board::findNearestStation()
{
	int pos = players[turn]->getPosition();
	if (pos == 7)
	{
		players[turn]->setPosition(15);
		reprint();
		return findProperty(15);
	}
	else if (pos == 22)
	{
		players[turn]->setPosition(25);
		reprint();
		return findProperty(25);
	}
	else if (pos == 36)
	{
		players[turn]->setPosition(5);
		reprint();
		players[turn]->addMoney(500);
		cout << players[turn]->getName() << " colected 500!" << endl;
		pause();
		return findProperty(5);
	}
}

void Board::save()
{
	ofstream prop,player,board;
	prop.open("prop.txt");
	player.open("player.txt");
	board.open("board.txt");

	//saving board
	board << dice << " " << playerSize << " " << turn;
	board.close();

	//saving properties
	for (int x = 0; x < 28; x++)
	{
		prop << properties[x]->getname() << ", " << properties[x]->getGroup() << " " << properties[x]->getpos() << " " << properties[x]->getpropertytype() << " " << properties[x]->getcost() << " " << properties[x]->getrent() << " " << properties[x]->getDefaultRent() << " " << properties[x]->getMortgaged();
		if (properties[x]->getpropertytype() == 1)
		{
			UpgradableProperty* temp = dynamic_cast<UpgradableProperty*>(properties[x]);
			prop << " " << temp->getHouse() << " " << temp->getShop() << " " << temp->getHotel() << " " << temp->getWifi() << " " << temp->getGas() << " " << temp->getElectricity();
		}
		if (x != 27)
		{
			prop << endl;
		}
	}
	prop.close();

	//saving players
	for (int x = 0; x < playerSize; x++)
	{
		player << players[x]->getName() << " " << players[x]->getPosition() << " " << players[x]->getBankrupt() << " " << players[x]->getPropertySize() << " " << players[x]->getJailCard() << " " << players[x]->getInJail() << " " << players[x]->getJailCount() << " " << players[x]->getMoney() << " " << players[x]->getcolour().r << " " << players[x]->getcolour().g << " " << players[x]->getcolour().b << " " << players[x]->getMortgageProperties();
		for (int y = 0; y < players[x]->getPropertySize(); y++)
		{
			player <<" "<<players[x]->PropertyPos(y);
		}
		if (x != playerSize - 1)
		{
			player << endl;
		}
	}
	player.close();
}

void Board::load()
{
	ifstream board, prop, player;
	board.open("board.txt");
	prop.open("prop.txt");
	player.open("player.txt");

	//loading board
	board >> dice >> playerSize >> turn;
	board.close();

	//loading properties
	char name[30], group[30];
	int pos, type, house, hotel, shop, wifi, gas, electricity;
	float cost, rent, drent;
	bool mortgage;

	properties = new Property*[28];
	int count = 0;

	while (!prop.eof())
	{
		prop.getline(name, 30, ',');
		prop.ignore();
		prop >> group >> pos >> type >> cost >> rent >> drent >> mortgage;
		if (type == 1)
		{
			prop >> house >> shop >> hotel >> wifi >> gas >> electricity;
		}
		prop.ignore();
		if (type == 1)
		{
			UpgradableProperty* u = new UpgradableProperty(name, group, pos, type, cost, drent);
			for (int x = 0; x < house; x++)
			{
				u->incHouse();
			}
			for (int x = 0; x < shop; x++)
			{
				u->incShop();
			}
			for (int x = 0; x < hotel; x++)
			{
				u->incHotel();
			}
			for (int x = 0; x < wifi; x++)
			{
				u->setWifi();
			}
			for (int x = 0; x < gas; x++)
			{
				u->setGas();
			}
			for (int x = 0; x < electricity; x++)
			{
				u->getElectricity();
			}
			u->setRent(rent);
			u->setMortgage(mortgage);
			properties[count++] = u;
		}
		else
		{
			NonUpgradable* n = new NonUpgradable(name, group, pos, type, cost, drent);
			n->setRent(rent);
			n->setMortgage(mortgage);
			properties[count++] = n;
		}
	}
	prop.close();

	//loading players
	players = new Player*[playerSize];
	char pname[30];
	bool bankrupt, jailCard, inJail;
	int ppos,size, jailCount, r, g, b, mortgageProps,proppos;
	float money;
	colour cl;
	for (int x = 0; x < playerSize; x++)
	{
		player >> pname >> ppos >> bankrupt >> size >> jailCard >> inJail >> jailCount >> money >> r >> g >> b >> mortgageProps;
		cl.r = r; cl.g = g; cl.b = b;
		players[x] = new Player(pname, ppos, cl,bankrupt,inJail,jailCount,money,jailCard,mortgageProps);
		for (int i = 0; i < size; i++)
		{
			player >> proppos;
			players[x]->AddProperty(findProperty(proppos));
		}
	}
	player.close();
}

void Board::upgrade()
{
	int op;
	a:
	system("cls"); reprint();
	cout << "Select property to upgrade: " << endl;
	for (int x = 0; x < players[turn]->getPropertySize(); x++)
	{
		cout << x + 1 << ") " << players[turn]->PropertyName(x) << endl;
	}
	cout << "0) Continue" << endl;
	cin >> op;
	if (op>players[turn]->getPropertySize() ||op<0)
	{
		cout << "Invlaid option selecetd!" << endl;
		goto a;
	}

	if (op != 0)
	{
		Property* pr = findProperty(players[turn]->PropertyPos(op - 1));
		UpgradableProperty* upp = dynamic_cast<UpgradableProperty*>(pr);

		if (pr->getpropertytype() == 2)
		{
			cout << "This property is unupgradable!" << endl;
			pause();
		}
		else
		{
			int upgrades = upp->getHouse() + upp->getHotel() + upp->getShop();

			if (!checkOwnershipOfGroup(pr))
			{
				cout << "You cannot upgrade!" << endl;
				cout << "You need to own all properties of this group!" << endl;
				pause();
			}
			else
			{
				upp->printProperty();
				cout << endl;
				cout << "1) House" << endl;
				cout << "2) Shop" << endl;
				cout << "3) Hotel" << endl;
				cout << "4) Wifi" << endl;
				cout << "5) Gas Connection" << endl;
				cout << "6) Electricity" << endl;
				cin >> op;
				if (op == 1)
				{
					if (checkHousesInGroup(pr))
					{
						if (players[turn]->getMoney() >= 100)
						{
							upp->incHouse();
							players[turn]->deductMoney(100);
							reprint();
							cout << "House built" << endl;
							pause();
						}
						else
						{
							cout << "You dont have enough money!" << endl;
							pause();
						}
					}
					else
					{
						cout << "House not built!" << endl;
						cout << "All properties of this group should have same number of houses!" << endl;
						pause();
					}
				}
				else if (op == 2)
				{
					if (checkShopsInGroup(pr))
					{
						if (checkHousesForShop(pr))
						{
							upp->incShop();
							upp->decHouse(3);
							reprint();
							cout << "Shop built!" << endl;
							pause();
						}
						else
						{
							cout << "Shop not built!" << endl;
							cout << "You need 3 houses in each property of this group to build shop!" << endl;
							pause();
						}
					}
					else
					{
						cout << "Shop not built!" << endl;
						cout << "All properties of this group should have same number of shops!" << endl;
						pause();
					}
				}
				else if (op == 3)
				{
					if (checkHotelsInGroup(pr))
					{
						if (checkRequirementsForHotel(pr))
						{
							upp->incHotel();
							upp->decHouse(4);
							upp->decShop(2);
							reprint();
							cout << "Hotel built!" << endl;
							pause();
						}
						else
						{
							cout << "Hotel not built!" << endl;
							cout << "You need 2 shops and 4 houses to build a hotel" << endl;
							pause();
						}
					}
					else
					{
						cout << "Hotel not built!" << endl;
						cout << "All properties of this group should have same number of Hotels!" << endl;
						pause();
					}
				}
				else if (op == 4)
				{
					if (upp->getWifi() < upgrades)
					{
						if (players[turn]->getMoney() >= 30)
						{
							upp->setWifi();
							players[turn]->deductMoney(30);
							reprint();
							cout << "Wifi added!" << endl;
							pause();
						}
						else
						{
							cout << "You dont have enough money!" << endl;
							pause();
						}
					}
					else
					{
						cout << "Wifi is already upgraded in all buildings!" << endl;
						pause();
					}
				}
				else if (op == 5)
				{
					if (upp->getGas() < upgrades)
					{
						if (players[turn]->getMoney() >= 50)
						{
							upp->setGas();
							players[turn]->deductMoney(50);
							reprint();
							cout << "Gas connection added!" << endl;
							pause();
						}
						else
						{
							cout << "You dont have enough money!" << endl;
							pause();
						}
					}
					else
					{
						cout << "Gas connection is already upgraded" << endl;
						pause();
					}
				}
				else if (op == 6)
				{
					if (upp->getElectricity() < upgrades)
					{
						if (players[turn]->getMoney() >= 50)
						{
							upp->setElectricity();
							players[turn]->deductMoney(50);
							reprint();
							cout << "Electricity added!" << endl;
							pause();
						}
						else
						{
							cout << "You dont have enough money!" << endl;
						}
					}
					else
					{
						cout << "Electricity is already upgraded" << endl;
						pause();
					}
				}
				else
				{
					cout << "Invalid option!" << endl;
				}
				goto a;
			}
		}
	}
}
