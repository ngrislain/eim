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

#include "utils/plot.h"
#include "utils/omega.h"
#include "market/demand.h"

using namespace std;

Tests::Tests() {
	cout << "Running tests" << endl;
	omega();
	demand();
	omega();
}

void Tests::demand() {
	cout << endl <<  "Testing Demand" << endl;
	Plot p;
	Omega o;
	vector<double> x, y;
	Demand d(o);
	for (int i = 0; i < 10000; i++) {
		time_t enter = chrono::system_clock::to_time_t(d.enter_date());
		time_t travel = chrono::system_clock::to_time_t(d.travel_date());
		x.push_back(enter);
		cout << "DEBUG Tests::demand pre ++o" << endl;
		++o;
		cout << "DEBUG Tests::demand post ++o" << endl;
		y.push_back(d.id());
		//cout << d << endl;
	}
	p.plot(x, y, ", 'ro', alpha=0.5");
}

void Tests::omega() {
	cout << endl <<  "Testing Omega" << endl;
	Omega o(20);
	std::normal_distribution<double> u{2,1};
	cout << "o = " << o << endl;
	auto a = o(u);
	a = o(std::normal_distribution<double>{3,1});
	auto b = o.integer();
	auto c = o.real();
	auto d = o.norm();
	auto e = o(std::exponential_distribution<>(0.1));
	auto A = o(u, array<double, 5>{});
	array<unsigned long, 5> data;
	auto B = o.integer(data);
	auto C = o.real(array<double, 5>{});
	auto D = o.norm(array<double, 5>{});
	auto E = o(std::exponential_distribution<>(0.01), array<double, 10>{});
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
		cout << "e = " << e << endl;
		cout << "e = " << e << endl;
		cout << "A = " << A << endl;
		cout << "A = " << A << endl;
		cout << "B = " << B << endl;
		cout << "C = " << C << endl;
		cout << "D = " << D << endl;
		cout << "E = " << E << endl;
		cout << "E = " << E << endl;
	}
}

