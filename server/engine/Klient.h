//#pragma once

//#ifndef __KLIENT_H__
//#define __KLIENT_H__

#include "Gracz.h"

#include <boost/python.hpp>
using namespace boost::python;


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
	void convert_and_update(list board);
	int planszaCopy[8][8];
	bool ready = false;
	int graczID;
};

BOOST_PYTHON_MODULE(Klient){
		class_<GraczWrap, boost::noncopyable>("Gracz")
				.def("getID", pure_virtual(&Gracz::getID))
				.def("update", pure_virtual(&Gracz::update))
				.def("getBestMove", pure_virtual(&Gracz::getBestMove))
//				.def("tru", pure_virtual(&Base::tru))
//				.def("getK", &Gracz::getK)
//				.def("getW", &Gracz::getW)
//				.def("getPrevK", &Gracz::getPrevK)
//				.def("getPrevW", &Gracz::getPrevW)
		;

		class_<Klient, bases<Gracz> >("Klient", init<int>())
		        .def("convert_and_update", &Klient::convert_and_update);
}


//#endif