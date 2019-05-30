//#pragma once

#ifndef _GRA_H_
#define _GRA_H_
#include "Plansza.h"
#include "Gracz.h"
#include "Klient.h"
#include "Komputer.h"
#include "Move.h"
#include <iostream>

class Gra
{
public:
	Gra();
	~Gra();
	void drukuj();
	void play();
	void player1notify();
	void player2notify();

private:
	Plansza plansza;
	Gracz* player1;
	Gracz* player2;
	const int kolumny = 8;
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