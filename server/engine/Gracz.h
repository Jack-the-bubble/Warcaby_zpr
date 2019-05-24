#pragma once
#include "Move.h"
class Gracz
{
public:
	Gracz();
	virtual ~Gracz();
	virtual int getID() = 0;
	virtual int getPrevK() { return 0; };    //to usuniemy jak bedzie komputer
	virtual int getPrevW() { return 0; };	//to usuniemy jak bedzie komputer
	virtual int getK() { return 0; };	//to usuniemy jak bedzie komputer
	virtual int getW() { return 0; };	//to usuniemy jak bedzie komputer
	virtual void update (const int plansza[8][8]) = 0;
	virtual Move getBestMove() 
	{
		Move any;
		return any;
	};
	int boardCopy[8][8];
	const int size_ = 8;
	//int pomBoard[8][8]; //plansza pomocnicza
};

