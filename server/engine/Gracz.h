#pragma once
#include "Move.h"
class Gracz
{
public:
	Gracz();
	virtual ~Gracz();
	virtual int getID() = 0;
	virtual void update (const int plansza[8][8]) = 0;
	virtual Move getBestMove() = 0;
	virtual void oponentMove(Move oponentMove) { };
	int boardCopy[8][8];
	const int size_ = 8;

};

