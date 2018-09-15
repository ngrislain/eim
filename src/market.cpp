/*
 * market.cpp
 *
 *  Created on: 13 sept. 2018
 *      Author: ngrislain16
 */

#include "market.h"
#include <random>
#include <cmath>
#include "json.h"

void Agent::draw(Generator &generator) {
	id_ = generator();
	std::normal_distribution<double> normal{};
	features_[constant_feature] = 1;
	for (int i=1; i<feature_dim; i++) {
		features_[i] = normal(generator);
	}
}

double Driver::days_before_departure() const {
	return 20*std::exp(0.5*feature(days_before_departure_feature));
}

std::ostream& operator<<(std::ostream& os, const Driver& d) {
	json::Object result;
	result.set("type", "Driver")
			.set("id", d.id())
			.set<json::Array>("features");
	for (int i=1; i<feature_dim; i++) {
		result.get<json::Array>("features").add(d.feature(i));
	}
	result.set("days_before_departure", d.days_before_departure());
	return os;
}

double Passenger::days_before_departure() const {
	return 15*std::exp(0.5*feature(days_before_departure_feature));
}

std::ostream& operator<<(std::ostream& os, const Passenger& p) {
	os << "{" << std::endl <<
				"  \"type\":\"Passenger\"," << std::endl <<
				"  \"id\":\"" << std::hex << p.id() << "\"," << std::endl <<
				"  \"features\":[" << p.feature(0);
		for (int i=1; i<feature_dim; i++) {
			os << ", " << p.feature(i);
		}
		os << "]," << std::endl <<
				"  \"days_before_departure\":" << p.days_before_departure() << std::endl <<
				"}";
		return os;
}
