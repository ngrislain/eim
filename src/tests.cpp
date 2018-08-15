/*
 * tests.cpp
 *
 *  Created on: 13 août 2018
 *      Author: ngrislain16
 */

#include "tests.h"

#include <iostream>
#include <random>

#include "utils/omega.h"

using namespace std;

Tests::Tests() {
	cout << "Running tests" << endl;
	omega();
}

void Tests::omega() {
	cout << endl <<  "Testing Omega" << endl;
	Omega o(20);
	std::normal_distribution<double> u{2,1};
	cout << "o = " << o << endl;
	auto a = o(u);
	auto b = o(u);
	cout << "o = " << o << endl;

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "a() = " << a() << endl;
	cout << "b() = " << b() << endl;
	cout << "++o" << endl; ++o;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "++o" << endl; ++o;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
}

