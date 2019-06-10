#ifndef __KLIENT_H__
#define __KLIENT_H__

#include "Gracz.h"
#include "Move.h"
#include <iostream>

#include <boost/python.hpp>
using namespace boost::python;
typedef boost::python::list pyList;

/**
 * wrapper z biblioteki boost::python do eksponowania metod z klasy Gracz
 * */
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
	virtual void update(const int plansza[8][8]); /**pusta*/
	virtual int getID();				/**zwraca graczID*/
	virtual Move getBestMove();			/**zwraca bestMove*/
	void set(int i);					/**ustawia test*/
	int get();							/**zwraca test*/
	void moveUpdate(int begMov_x,int  begMov_y,int destMov_x, int destMov_y, pyList cap); /**zapisuje ruch klienta*/
	int test;
	int graczID; 									/**< identyfikator gracza */
};


#endif