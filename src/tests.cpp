/*
 * tests.cpp
 *
 *  Created on: 13 août 2018
 *      Author: ngrislain16
 */

#include "tests.h"

#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <type_traits>
#include <algorithm>

#include "json.h"
#include "omega.h"
#include "market.h"

// Create an ad-hoc class
class RandomVector : RandomVariable {
public:
	std::vector<double> vector;
	RandomVector(Omega &o) : RandomVariable(o) {};
	void draw(Generator &g) override {
		vector.clear();
		for (int i=0; i<3; i++) {
			vector.push_back(std::normal_distribution<double>()(g));
		}
	};

};

void tests::omega() {
	std::cout << std::endl << "Running omega tests" << std::endl;
	Omega o;
	RandomVector rv(o);
	++o;
	++o;
	std::cout << o << std::endl;
	++o;
	std::cout << o << std::endl;
	Omega o1(2), o2(2);
	RandomVector rv1(o1), rv2(o2);
	std::cout << rv.vector.data()[1] << std::endl;
	++o1; ++o2;++o2;
	std::cout << rv1.vector.data()[1] << " " << rv2.vector.data()[1] << std::endl;
	++o1; ++o2;++o2;
	std::cout << rv1.vector.data()[1] << " " << rv2.vector.data()[1] << std::endl;
}

void tests::market() {
	std::cout << std::endl << "Running market tests" << std::endl;
	Omega o;
	json::array<Driver> drivers;
	for (int i=0; i<1000; i++) {
		drivers.push_back(Driver(o));
	}
	std::cout << o;
	++o;
	std::cout << o;
	std::ofstream file;
	file.open("/tmp/eim_passengers.json", std::ofstream::out);
	file << drivers;
	file.close();
}

