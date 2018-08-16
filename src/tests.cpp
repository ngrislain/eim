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
	auto b = o();
	auto c = o.norm();
	auto d = o.unif();
	auto array = o.array<std::normal_distribution<double>, 5>(u);
	auto brray = o.array<20>();
	auto crray = o.unif_array<10>();
	auto drray = o.norm_array<5>();
	cout << "o = " << o << endl;

	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "c = " << c << endl;
	cout << "d = " << d << endl;
	cout << "a() = " << a() << endl;
	cout << "b() = " << b() << endl;
	cout << "c() = " << c() << endl;
	cout << "d() = " << d() << endl;
	for (int i=0; i<10; i++) {
		cout << "++o" << endl; ++o;
		cout << "a = " << a << endl;
		cout << "b = " << b << endl;
		cout << "c = " << c << endl;
		cout << "d = " << d << endl;
		cout << "array = " << array << endl;
		cout << "array = " << array << endl;
		cout << "brray = " << brray << endl;
		cout << "crray = " << crray << endl;
		cout << "drray = " << drray << endl;
	}
}

