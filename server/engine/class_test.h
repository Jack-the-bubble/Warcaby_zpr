//
// Created by ig-88 on 18.05.19.
//

#ifndef WARCABY_4_CLASS_TEST_H
#define WARCABY_4_CLASS_TEST_H

#include <boost/python.hpp>

struct World{
	void set(std::string msg);
	std::string greet();
	std::string msg;
};


using namespace boost::python;

BOOST_PYTHON_MODULE(class_test){
		class_<World>("World")
				.def("greet", &World::greet)
				.def("set", &World::set)
		;
}
#endif //WARCABY_4_CLASS_TEST_H
