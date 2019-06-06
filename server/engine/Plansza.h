//#pragma once
#ifndef _PLANSZA_H_
#define _PLANSZA_H_

#include "Move.h"

/**
 *  \brief     Glowna klasa planszy gry
 *  \author    Katarzyna Seweryn
 *  \date      2019
 */
class Plansza
{
public:
	Plansza();
	~Plansza();
	void makeMove(Move);
	bool isWin();
	int plansza[8][8];  /**< Glowna plansza gry */
	const int getPlansza(int, int);
private:	
	const int KOLUMNY = 8; /**< Rozmiar planszy */
};

#endif