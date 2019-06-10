//
// Created by Marcin Skrzypkowski on 30.05.19.
//

/**
 *  \brief     plik służący do eksponowania klas i ich metod do pythona
 *  \author    Marcin Skrzypkowski
 *  \date      2019
 */

#ifndef WARCABY_4_ENGINE_H
#define WARCABY_4_ENGINE_H

#include "Gra.h"

BOOST_PYTHON_MODULE(engine){
	class_<GraczWrap, boost::noncopyable>("Gracz")
		.def("getID", pure_virtual(&Gracz::getID))
		.def("update", pure_virtual(&Gracz::update))
		.def("getBestMove", pure_virtual(&Gracz::getBestMove))
		;


	class_<Klient, bases<Gracz> >("Klient", init<>())
		.def("oponentMove", &Klient::oponentMove)
		;

	class_<Move>("Move", init<>())
	    .def(init<int, int, int, int, int, int, int>())
		.def("createKing", &Move::createKing)
		.def("addCaptured", &Move::addCaptured)
		;

	class_<Plansza>("Plansza", init<>())
		.def("makeMove", &Plansza::makeMove)
		.def("isWin", &Plansza::isWin)
		.def("getPlansza", &Plansza::getPlansza)
		;

	class_<Komputer, bases<Gracz> >("Komputer", init<>());

	class_<Gra>("Gra", init<>())
	    .def("drukuj", &Gra::drukuj)
        .def("player1notify", &Gra::player1notify)
        .def("player2notify", &Gra::player2notify)
        .def("klientMoveUpdate", &Gra::klientMoveUpdate)
        .def("computerUpdate", &Gra::computerUpdate)
        .def("changePlansza", &Gra::changePlansza)
        .def("convertAndSend", &Gra::convertAndSend)
        .def("assignID", &Gra::assignID)
        .def("getID", &Gra::getID)
        .def("klientGet", &Gra::klientGet)
		.def("klientSet", &Gra::klientSet)
        ;
}

#endif //WARCABY_4_ENGINE_H
