//#pragma once
#ifndef __GRACZ_H_
#define __GRACZ_H_

#include "Move.h"

/**
 *  \brief     Abstrakcyjna klasa gracza
 *  \author    Katarzyna Seweryn
 *  \date      2019
 */

class Gracz
{
public:
	Gracz();
	virtual ~Gracz();
	virtual int getID() = 0;
	virtual void update (const int plansza[8][8]) = 0;
	virtual Move getBestMove() = 0;
	virtual void oponentMove(Move oponentMove) {};
	int boardCopy[8][8]; /**< plansza gry przekazana do analizy dla gracza */
	const int SIZE = 8; /**< rozmiar planszy */

};

#endif