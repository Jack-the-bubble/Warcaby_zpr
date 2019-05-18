//
// Created by ig-88 on 18.05.19.
//

#include "class_test.h"


void World::set(std::string msg) {
	this->msg = msg;
}

std::string World::greet() {
	return msg;
}

//using namespace boost::python;
//
//BOOST_PYTHON_MODULE(class_test){
//		class_<World>("World")
//				.def("greet", &World::greet)
//				.def("set", &World::set)
//		;
//}