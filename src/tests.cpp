/*
 * tests.cpp
 *
 *  Created on: 13 août 2018
 *      Author: ngrislain16
 */

#include "tests.h"

#include <iostream>

#include "utils/omega.h"

using namespace std;

Tests::Tests() {
	cout << "Running tests" << endl;

	cout << endl <<  "Testing Omega" << endl;
	Omega &omega = Omega::instance;
	cout << "Omega::instance() -> " << Omega::instance() << endl;
	cout << "Omega::instance() -> " << Omega::instance() << endl;
	cout << "++omega" << endl;
	++omega;
	cout << "Omega::instance() -> " << Omega::instance() << endl;

	cout << endl << "Testing Omega::Generator" << endl;

	auto g_1 = omega[1];
	auto g_1_alt = Omega::Generator<Omega>(Omega::instance, 1);
	auto g_2 = omega[2];
	auto g_1_1 = g_1[1];
	auto g_1_2 = g_1[2];
	auto g_2_1 = g_2[1];
	auto g_2_1_alt = omega[2][1];
	cout << "g_1() -> " << g_1() << endl;
	cout << "g_1_alt() -> " << g_1_alt() << endl;
	cout << "g_2() -> " << g_2() << endl;
	cout << "g_1_1() -> " << g_1_1() << endl;
	cout << "g_1_2() -> " << g_1_2() << endl;
	cout << "g_2_1() -> " << g_2_1() << endl;
	cout << "g_2_1_alt() -> " << g_2_1_alt() << endl;
	cout << "++omega" << endl;
	++omega;
	cout << "g_1() -> " << g_1() << endl;
	cout << "g_2() -> " << g_2() << endl;
	cout << "g_2() -> " << g_2() << endl;
	cout << "g_1_1() -> " << g_1_1() << endl;
	cout << "g_1_2() -> " << g_1_2() << endl;
	cout << "g_2_1() -> " << g_2_1() << endl;
	cout << bind(uniform_int_distribution<int>(1,6), omega[0])() << endl;
}

