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
	int plansza[8][8];  			/**< Glowna plansza gry */
	const int getPlansza(int, int); /**zwraca wartosc na podanym polu*/
	int bicie(int, int,int,int,int); //usuwa zbity pionek
	int getPionkiCzarne(); 			/**zwraca liczbe czarnych pionkow*/
	int getPionkiBiale(); 			/**zwraca liczbe bialych pionkow*/
	bool damka(int, int, int);
private:
	int pionkiBiale;   				/**liczba pionkow gracza o ID = 1*/
	int pionkiCzarne;  				/**liczba pionkow gracza o ID = -1*/
	const int KOLUMNY = 8;			/**< Rozmiar planszy */
	bool damkaDone = false;
};

#endif