/*
 * tests.cpp
 *
 *  Created on: 13 août 2018
 *      Author: ngrislain16
 */

#include "tests.h"

#include <cstdlib>
#include <memory>
#include <iostream>
#include <fstream>
#include <random>
#include <vector>

#include "json.h"
#include "omega.h"
#include "market.h"

void tests::json() {
	std::cout << std::endl << "Running json tests" << std::endl;
	Omega o;
	json::Array a;
	a.add(2).add(3.).add("Hello").add<json::Array>();
	a.add<json::Object>().get<json::Object>()
			.set("test", "ok")
			.set("other", "value");
			//.set("passenger", new Passenger(o));
	std::cout << a << std::endl;
}

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
	json::Array drivers;
	json::Array passengers;
//	for (int i=0; i<1000; i++) {
//		drivers.push_back(std::unique_ptr<json::Serializable>(new Driver(o)));
//		passengers.push_back(std::unique_ptr<json::Serializable>(new Passenger(o)));
//	}
	++o;

	std::system("mkdir /tmp/eim");
	std::ofstream file;

	file.open("/tmp/eim/drivers.json", std::ofstream::out);
	file << drivers;
	file.close();

	file.open("/tmp/eim/passengers.json", std::ofstream::out);
	file << passengers;
	file.close();
}

