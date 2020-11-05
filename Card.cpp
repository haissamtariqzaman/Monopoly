#include"Card.h"
#include<fstream>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include <stdlib.h>
#include <time.h>
using namespace std;

Card::Card(char* a)
{
	currCard = 0;
	char line[200];
	ifstream fin;
	fin.open(a);
	if (fin.is_open())
	{
		instructions = new instruction[15];
		for (int i = 0; i < 15;i++)
		{
			fin.getline(line, 200, '\n');
			instructions[i].setText(line);
			instructions[i].setId(i);
		}
	}
	else
		cout << "Error. File not found." << endl;
}

void Card::shuffle()
{
	int a = 1;
	srand(time(0));
	a = rand()%3;
	if (a == 0)
	{
		instruction* temp = new instruction[15];
		for (int i = 0, j = 14; i < 15, j >= 0; i++, j--)
		{
			temp[i].setText(instructions[j].getText());
			temp[i].setId(instructions[j].getId());
		}
		delete[] instructions;
		instructions = temp;
	}
	if (a == 1)
	{
		instruction* temp = new instruction[15];
		for (int i = 0, j = 14,k = 8,l = 6; i < 8, j >= 7,k < 15,l >= 0; i++, j--, k++, l--)
		{
			temp[i].setText(instructions[j].getText());
			temp[i].setId(instructions[j].getId());
			
			temp[k].setText(instructions[l].getText()); 
			temp[k].setId(instructions[l].getId());
		}
		delete[] instructions;
		instructions = temp;
	}
	if (a == 2)
	{
		instruction* temp = new instruction[15];
		for (int i = 0, j = 14, k = 5, l = 9,m = 10,n = 4; i < 8, j >= 10, k < 10, l >= 5,m < 15,n >= 0; i++, j--, k++, l--,m ++, n--)
		{
			temp[i].setText(instructions[j].getText());
			temp[i].setId(instructions[j].getId());

			temp[k].setText(instructions[l].getText());
			temp[k].setId(instructions[l].getId());

			temp[m].setText(instructions[n].getText());
			temp[m].setId(instructions[n].getId());
		}
		delete[] instructions;
		instructions = temp;
	}
}

Card::~Card()
{
	delete[] instructions;
}

instruction Card::returnInstruction()
{
	if (currCard > 14)
	{
		currCard = 0;
	}
	return instructions[currCard++];
}