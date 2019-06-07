//#pragma once

#ifndef __KLIENT_H__
#define __KLIENT_H__

#include "Gracz.h"
#include "Move.h"
#include <iostream>

#include <boost/python.hpp>
using namespace boost::python;
typedef boost::python::list pyList;
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

/**
 *  \brief     Klasa klienta(uzytkownika) wykonujacego ruch
 *  \author    Katarzyna Seweryn
 *  \author    Marcin Skrzypkowski
 *  \date      2019
 */
class Klient :
	public Gracz
{
public:
	Klient();
	~Klient();
	virtual void update(const int plansza[8][8]);
	virtual int getID();
	virtual void oponentMove(Move oponentMove);
	virtual Move getBestMove();
	void set(int i);
	int get();
	void convert_and_update(boost::python::list board);
//<<<<<<< HEAD
	void moveUpdate(int begMov_x,int  begMov_y,int destMov_x, int destMov_y, pyList cap);
	int planszaCopy[8][8];
	bool ready = false;
	Move putLatestMove(boost::python::list move);
	Move latestMove;
//=======
	int test;
	int graczID; /**< identyfikator gracza */
//>>>>>>> fc4467e51dbd79f216efd7794bb93c5f319c6835
};


#endif