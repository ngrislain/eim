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

std::ostream& Agent::json(std::ostream& os, int indent) const {
	json::Object result;
	result.set("type", "Agent")
			.set("id", id())
			.set<json::Array>("features");
	for (int i=1; i<feature_dim; i++) {
		result.get<json::Array>("features").add(feature(i));
	}
	return result.json(os);
}

double Driver::days_before_departure() const {
	return 20*std::exp(0.5*feature(days_before_departure_feature));
}

std::ostream& Driver::json(std::ostream& os, int indent) const {
	json::Object result;
	result.set("type", "Driver")
			.set("id", id())
			.set<json::Array>("features");
	for (int i=1; i<feature_dim; i++) {
		result.get<json::Array>("features").add(feature(i));
	}
	result.set("days_before_departure", days_before_departure());
	return result.json(os);
}

double Passenger::days_before_departure() const {
	return 15*std::exp(0.5*feature(days_before_departure_feature));
}

std::ostream& Passenger::json(std::ostream& os, int indent) const {
	json::Object result;
	result.set("type", "Passenger")
			.set("id", id())
			.set<json::Array>("features");
	for (int i=1; i<feature_dim; i++) {
		result.get<json::Array>("features").add(feature(i));
	}
	result.set("days_before_departure", days_before_departure());
	return result.json(os);
}
