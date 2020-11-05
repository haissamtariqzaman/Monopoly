#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<iostream>
using namespace std;

class instruction
{
public:
	instruction();
	//{
	//	text = new char('\0');
	//}
	instruction(const instruction& i);
	//{
	//	text = new char[strlen(i.text) + 1];
	//	strcpy(text, i.text);
	//}
	~instruction(); /*{ delete[] text; }*/
	void setText(char* t);
	//{
	//	delete[] text;
	//	text = new char[strlen(t) + 1];
	//	strcpy(text, t);
	//}
	void setId(int i); /*{ id = i; }*/
	char* getText(); /*{ return text; }*/
	int getId(); /*{ return id; }*/
private:
	char* text;
	int id;
};

class Card
{
public:
	Card(char*);
	instruction returnInstruction();
	void shuffle();
	~Card();
private:
	instruction* instructions;
	int currCard;
};
