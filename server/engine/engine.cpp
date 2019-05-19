//
// Created by ig-88 on 19.05.19.
//

#include "Klient.h"
#include <boost/python.hpp>

using namespace boost::python;


class GraczWrap : public Gracz, public wrapper<Gracz>
{
public:
	virtual int getID(){
		return this->get_override("getID")();
	}

	virtual void update(/*const int plansza[8][8]*/){
		this->get_override("update")();
	}
};



BOOST_PYTHON_MODULE(engine){
		class_<GraczWrap, boost::noncopyable>("Gracz")
				.def("getID", pure_virtual(&Gracz::getID))
				.def("update", pure_virtual(&Gracz::update))
//				.def("tru", pure_virtual(&Base::tru))
				.def("getK", &Gracz::getK)
				.def("getW", &Gracz::getW)
				.def("getPrevK", &Gracz::getPrevK)
				.def("getPrevW", &Gracz::getPrevW)
		;

		class_<Klient, bases<Gracz> >("Klient", init<int>());
}