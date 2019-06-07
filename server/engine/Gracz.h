//#pragma once
#ifndef __GRACZ_H_
#define __GRACZ_H_

#include "Move.h"
#include <boost/python.hpp>
typedef boost::python::list pyList;

class Gracz
{
public:
	Gracz();
	virtual ~Gracz();
	virtual int getID() = 0;
	virtual void update (const int plansza[8][8]) = 0;
	virtual Move getBestMove() = 0;
	virtual void oponentMove(Move oponentMove) {};
	virtual void moveUpdate(int begMov_x,int  begMov_y,int destMov_x, int destMov_y, pyList cap) {};
	int boardCopy[8][8];
	const int SIZE = 8;

};

#endif