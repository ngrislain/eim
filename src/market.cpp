/*
 * market.cpp
 *
 *  Created on: 13 sept. 2018
 *      Author: ngrislain16
 */

#include "market.h"
#include <random>
#include <cmath>

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
	os << "{" << std::endl <<
			"  \"type\":\"Driver\"," << std::endl <<
			"  \"id\":\"" << std::hex << d.id() << "\"," << std::endl <<
			"  \"features\":[" << d.feature(0);
	for (int i=1; i<feature_dim; i++) {
		os << ", " << d.feature(i);
	}
	os << "]," << std::endl <<
			"  \"days_before_departure\":" << d.days_before_departure() << std::endl <<
			"}";
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
