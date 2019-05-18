//
// Created by ig-88 on 18.05.19.
//
#include <iostream>
#include <string>

#include "Gracz.h"

#include <boost/python.hpp>
using namespace boost::python;

//class Base
//{
//public:
//	virtual ~Base() {}
//	virtual std::string name() const { return "Base";}
//	virtual int get() = 0;
//
//	virtual bool tru() = 0;
//};
//
//class BaseWrap : public Base, public wrapper<Base>
//{
//public:
//	virtual int get()
//	{
//		return this->get_override("get")();
//	}
//
//	virtual bool tru(){
//		return this->get_override("tru")();
//	}
//};
//
//class Derived: public Base{
//public:
//	virtual std::string name() const { return "Derived";}
//	virtual int get() {
//		return 3;
//	}
//	virtual bool tru(){
//		return true;
//	}
//};

//class Gracz {
//public:
//	Gracz(){}
//	virtual ~Gracz(){}
//	virtual int getID() = 0;
//};


class Gra_wrap: public Gracz, public wrapper<Gracz>{
public:
	virtual int getID(){
		return this->get_override("getID")();
	}
};

class Klient:public Gracz{
public:
	Klient(){};
	virtual ~Klient(){};
	virtual int getID(){
		return 2;
	}

};

BOOST_PYTHON_MODULE(deriv_list_test){
//		class_<BaseWrap, boost::noncopyable>("Base")
//				.def("get", pure_virtual(&Base::get))
//				.def("tru", pure_virtual(&Base::tru))
//				.def("name", &Base::name)
//		;
//
//		class_<Derived, bases<Base> >("Derived");

		class_<Gra_wrap, boost::noncopyable>("Gracz")
		        .def("getID", pure_virtual(&Gracz::getID))
		        ;
		class_<Klient, bases<Gracz> >("Klient");
}