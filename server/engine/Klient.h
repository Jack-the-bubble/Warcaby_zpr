//#pragma once

#ifndef __KLIENT_H__
#define __KLIENT_H__

#include "Gracz.h"
#include "Move.h"

#include <boost/python.hpp>
using namespace boost::python;

//class Move{};

class GraczWrap : public Gracz, public wrapper<Gracz>
{
public:
	virtual int getID(){
		return this->get_override("getID")();
	}

	virtual void update(const int plansza[8][8]){
		this->get_override("update")();
	}

	virtual Move getBestMove(){
		return this->get_override("getBestMove")();
	}

//	virtual Move getOponentMove(Move oponentMove){
//		return this->get_override("getOponentMove")();
//	}
};

class Klient :
	public Gracz
{
public:
	Klient(int);
	~Klient();
	virtual void update(const int plansza[8][8]);
	virtual int getID();
	virtual void oponentMove(Move oponentMove);
	virtual Move getBestMove();
	void convert_and_update(boost::python::list board);
	int planszaCopy[8][8];
	bool ready = false;
	int graczID;
};


#endif