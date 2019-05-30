//#pragma once
#ifndef _PLANSZA_H_
#define _PLANSZA_H_

#include "Move.h"
class Plansza
{
public:
	Plansza();
	~Plansza();
	void makeMove(Move);
	bool isWin();
	int plansza[8][8];
	const int getPlansza(int, int);
private:	
	const int kolumny = 8;
};

#endif