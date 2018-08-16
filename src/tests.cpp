/*
 * tests.cpp
 *
 *  Created on: 13 août 2018
 *      Author: ngrislain16
 */

#include "tests.h"

#include <iostream>
#include <random>
#include <vector>

#include "utils/omega.h"

using namespace std;

template<typename Container, typename Function>
void for_each(Container&& cont, Function f) {
    using std::begin;
    auto it = begin(cont);
    using std::end;
    auto end_it = end(cont);
    while (it != end_it) {
        f(*it);
        ++it;
    }
}

Tests::Tests() {
	cout << "Running tests" << endl;

	vector<double> v = {1,2,3};
	for_each(v,[](double x){cout << x << "," << endl;});


	omega();
}

void Tests::omega() {
	cout << endl <<  "Testing Omega" << endl;
	Omega o(20);
	std::normal_distribution<double> u{2,1};
	cout << "o = " << o << endl;
	auto a = o(u);
	auto b = o.integer();
	auto c = o.real();
	auto d = o.norm();
	array<double, 5> data;
	auto A = o(u, array<double, 5>{});
	auto B = o.integer(data);
	auto C = o.real(array<double, 5>{});
	auto D = o.norm(array<double, 5>{});
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
		cout << "A = " << A << endl;
		cout << "A = " << A << endl;
		cout << "B = " << B << endl;
		cout << "C = " << C << endl;
		cout << "D = " << D << endl;
	}
}

