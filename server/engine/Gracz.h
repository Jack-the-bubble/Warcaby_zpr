//#pragma once
#ifndef __GRACZ_H_
#define __GRACZ_H_

#include "Move.h"
#include <boost/python.hpp>
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
	virtual void update (const int plansza[8][8]) = 0;
	virtual Move getBestMove() = 0;
	virtual void oponentMove(Move oponentMove) {};
//<<<<<<< HEAD
	virtual void moveUpdate(int begMov_x,int  begMov_y,int destMov_x, int destMov_y, pyList cap) {};
	int boardCopy[8][8];
	const int SIZE = 8;
//=======
	int boardCopy[8][8]; /**< plansza gry przekazana do analizy dla gracza */
	const int SIZE = 8; /**< rozmiar planszy */
//>>>>>>> fc4467e51dbd79f216efd7794bb93c5f319c6835

};

#endif