#pragma once
#include "Player.h"
#include "Card.h"

class Board
{
public:
	Board(int);
	~Board();
	void play();
private:
	void rollDice();
	void display_Board(int = 140, int = 10);
	void display_player(int, int, int, int, int = 140, int = 10,int=0);
	void display_playerInfo(Player**,int,int=140,int=10);
	void printDice(int num, int = 140, int = 10);
	void reprint(bool=0);
	void playerOnProperty(int);
	void playerOnLandTax();
	void playerOnParking();
	void playerOnGoToPrison();
	void playerOnPropertyTax();
	void playerOnCommunityChest();
	void playerOnChance();
	Property* findProperty(int);
	void Auction(Property*);
	void nextTurn();
	void removePlayer(int);
	bool checkWinner();
	bool bankruptToBank();
	bool checkOwnershipOfGroup(Property*);
	bool checkHousesInGroup(Property*);
	bool checkHousesForShop(Property*);
	bool checkShopsInGroup(Property*);
	bool checkHotelsInGroup(Property*);
	bool checkRequirementsForHotel(Property*);
	Property* findNearestUtility();
	Property* findNearestStation();
	bool payMenu(float);
	void upgrade();
	void save();
	void load();
private:
	Player** players;
	Property** properties;
	int dice;
	Card communityChest;
	Card chance;
	int playerSize;
	int turn;
};