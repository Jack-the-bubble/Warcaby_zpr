//
// Created by ig-88 on 18.05.19.
//

#ifndef WARCABY_4_DERIV_TEST_H
#define WARCABY_4_DERIV_TEST_H

#include <boost/python.hpp>

class A {
public:
	A(){}
	int get() { return 0;}
};

class B {
public:
	B(){;;}
};

using namespace boost::python;

class vir_test: public A/*, wrapper<vir_test>*/{
public:
	vir_test(int b): a(b){}
	int get(){
		return a;
	}

private:
	int a;
};

class deriv_test: public B {
public:
	deriv_test(int x);
	void set(int x);
	int get();

private:
	int a;

};

BOOST_PYTHON_MODULE(deriv_test){
		class_<B>("B", no_init);

		class_<deriv_test, bases<B> >("deriv_test", init<int>())
		.def("get", &deriv_test::get)
		.def("set", &deriv_test::set)
		;

		class_<A>("A")
		        .def("get", &A::get);
		class_<vir_test, bases<A> >("vir_test", init<int>())
		        .def("get", &vir_test::get);
}

#endif //WARCABY_4_DERIV_TEST_H
