#pragma once
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

