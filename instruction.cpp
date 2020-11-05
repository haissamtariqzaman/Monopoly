#define _CRT_SECURE_NO_WARNINGS
#include "Card.h"

instruction::instruction()
{
	text = new char('\0');
}
instruction::instruction(const instruction& i)
{
	text = new char[strlen(i.text) + 1];
	strcpy(text, i.text);
	id = i.id;
}
instruction::~instruction(){ delete[] text; }
void instruction::setText(char* t)
{
	delete[] text;
	text = new char[strlen(t) + 1];
	strcpy(text, t);
}
void instruction::setId(int i){ id = i; }
char* instruction::getText(){ return text; }
int instruction::getId(){ return id; }