//#pragma once
#ifndef __GRACZ_H_
#define __GRACZ_H_

#include "Move.h"
#include <boost/python.hpp>
#include <iostream>
typedef boost::python::list pyList;

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
	void drukuj(const int board[8][8]);
	virtual void update (const int plansza[8][8]) = 0;
	virtual Move getBestMove() = 0;
	virtual void oponentMove(Move oponentMove) {};
	virtual void set(int i) {};
	int get() {};
	virtual void moveUpdate(int begMov_x,int  begMov_y,int destMov_x, int destMov_y, pyList cap) {};
	int boardCopy[8][8]; /**< plansza gry przekazana do analizy dla gracza */
	const int size_ = 8; /**< rozmiar planszy */
	Move bestMove;
};

#endif