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
	int bicie(int, int,int,int,int); //usuwa zbity pionek
	int getPionkiCzarne();
	int getPionkiBiale();
	bool damka(int, int, int);
private:
	int pionkiBiale;   //pionki gracza o ID = 1
	int pionkiCzarne;  //pionki gracza o ID = -1
	const int KOLUMNY = 8;/**< Rozmiar planszy */
	bool damkaDone = false;
};

#endif