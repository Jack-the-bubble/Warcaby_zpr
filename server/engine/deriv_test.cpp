//
// Created by ig-88 on 18.05.19.
//
#include <vector>
#include <iostream>
#include "deriv_test.h"

deriv_test::deriv_test(int x): a(x){}

void deriv_test::set(int x) {
	a = x;
}

int deriv_test::get() {
	return a;
}
