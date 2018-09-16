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
#include <valarray>

#include "json.h"
#include "omega.h"
#include "market.h"
#include "utils.h"

void tests::json() {
	std::cout << std::endl << "Running json tests" << std::endl;
	Omega o;
	json::Array a;
	a.add(2).add(3.).add("Hello").add<json::Array>();
	a.add<json::Object>().get<json::Object>()
			.set("test", "ok")
			.set("other", "value")
			.set("passenger", new market::Demand(o));
	++o;
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
	for (int i=0; i<1000; i++) {
		drivers.push_back(std::unique_ptr<json::Serializable>(new market::Supply(o)));
		passengers.push_back(std::unique_ptr<json::Serializable>(new market::Demand(o)));
	}
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

void tests::value() {
	int driver_size = 100;
	int passenger_size = 80;
	Omega o;
	market::SoftValue v(o);
	//market::TreatmentModifier m(o, 0.1, 0.5);
	market::SupplyTreatmentModifier m(o, 0.1, 0.6);
	++o;
	std::vector<market::Supply> drivers;
	std::vector<market::Demand> passengers;
	std::valarray<double> values(driver_size*passenger_size);

	for (int i=0; i<driver_size; i++) {
		drivers.push_back(market::Supply(o));
	}
	for (int j=0; j<passenger_size; j++) {
		passengers.push_back(market::Demand(o));
	}
	++o;
	for (int i=0; i<driver_size; i++) {
		for (int j=0; j<passenger_size; j++) {
			values[i*passenger_size+j] = m(drivers[i], passengers[j], v);
		}
	}
	json::Array result;
	for (int i=0; i<driver_size; i++) {
		result.add<json::Array>();
		for (int j=0; j<passenger_size; j++) {
			result.get<json::Array>(i).add(values[passenger_size*i + j]);
		}
	}
	std::system("mkdir /tmp/eim");
	std::ofstream file;
	file.open("/tmp/eim/value.json", std::ofstream::out);
	file << v << std::endl;
	file.close();
	file.open("/tmp/eim/value_representation.json", std::ofstream::out);
	file << result << std::endl;
	file.close();
}

void tests::modifier() {
	Omega o;
	market::TreatmentModifier tm(o);
	market::MatchingModifier mm(o);
	++o;
	std::system("mkdir /tmp/eim");
	std::ofstream file;
	file.open("/tmp/eim/treatment.json", std::ofstream::out);
	file << tm << std::endl;
	file.close();
	file.open("/tmp/eim/matching.json", std::ofstream::out);
	file << mm << std::endl;
	file.close();
}

void tests::utils() {
	std::cout << std::endl << "Running utils tests" << std::endl;
	Index<11,11> idx;
	std::cout << idx[3][2] << std::endl;
}

