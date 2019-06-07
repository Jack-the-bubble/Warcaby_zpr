//#pragma once

#ifndef _GRA_H_
#define _GRA_H_
#include "Plansza.h"
#include "Gracz.h"
#include "Klient.h"
#include "Komputer.h"
#include "Move.h"
#include <iostream>
//<<<<<<< HEAD
#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<Komputer> Kom;
typedef boost::shared_ptr<Klient> Kl;

typedef boost::python::list pyList;
//=======
/**
 *  \brief     Glowna klasa gry, jej metoda play jest petla glowna gry, kontroluje przeplyw ruchow i sprawdza terminalnosc planszy
 *  \author    Katarzyna Seweryn
 *  \date      2019
 */
//>>>>>>> fc4467e51dbd79f216efd7794bb93c5f319c6835
class Gra
{
public:
	Gra();
	~Gra();
	void drukuj();
	void play();
	void klientMoveUpdate(int begMov_x,int  begMov_y,int destMov_x, int destMov_y, pyList cap);
	void computerUpdate();
	void player1notify();
	void changePlansza();
	void player2notify();
	void assignID(int i);
	void reset();
	int getID();
	int klientGet();
	void klientSet(int i);

	pyList convertAndSend();

//private:
//<<<<<<< HEAD
//	Plansza plansza;
//	Gr player3;
//	Gracz* player1;
//	Gracz* player2;
//	const int kolumny = 8;
//=======

	Plansza plansza;  /**< plansza gry   */
	Kl player1;
	Kom player2;
	int ID_;
//	Klient* player1;  /**< wskaznik na gracza 1 */
//	Komputer* player2;  /**< wskaznik na gracza 2 */
	const int KOLUMNY = 8; /**< rozmiar planszy */
//>>>>>>> fc4467e51dbd79f216efd7794bb93c5f319c6835
};


//BOOST_PYTHON_MODULE(Gra){
//	class_<GraczWrap, boost::noncopyable>("Gracz")
//			.def("getID", pure_virtual(&Gracz::getID))
//			.def("update", pure_virtual(&Gracz::update))
//			.def("getBestMove", pure_virtual(&Gracz::getBestMove))
//			;
//
////				.def("tru", pure_virtual(&Base::tru))
////				.def("getK", &Gracz::getK)
////				.def("getW", &Gracz::getW)
////				.def("getPrevK", &Gracz::getPrevK)
////				.def("getPrevW", &Gracz::getPrevW)
//
//	class_<Klient, bases<Gracz> >("Klient", init<int>())
//			.def("convert_and_update", &Klient::convert_and_update);
//
//	class_<Move>("Move", init<>())
//	        .def("createKing", &Move::createKing)
//	        ;
//}








#endif