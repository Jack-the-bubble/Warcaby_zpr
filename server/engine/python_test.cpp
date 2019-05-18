//
// Created by ig-88 on 16.05.19.
//
#include <boost/python.hpp>

char const *greet(char const* a, int b){
	return a;
}

using namespace boost::python;

BOOST_PYTHON_MODULE(python_test){

		def("greet", greet);
}


int main(){

	return 0;
}