/*
 * market.cpp
 *
 *  Created on: 13 sept. 2018
 *      Author: ngrislain16
 */

#include "market.h"
#include <random>
#include <cmath>
#include <sstream>
#include <valarray>
#include "utils.h"
#include "json.h"

void market::Agent::draw(Generator &generator) {
	id_ = generator();
	std::normal_distribution<double> normal{};
	features_[constant_feature] = 1;
	for (int i=1; i<feature_dim; i++) {
		features_[i] = normal(generator);
	}
}

std::ostream& market::Agent::json(std::ostream& os, int indent) const {
	json::Object result;
	result.set("type", "Agent")
			.set("id", id())
			.set<json::Array>("features");
	for (int i=0; i<feature_dim; i++) {
		result.get<json::Array>("features").add(feature(i));
	}
	return result.json(os, indent);
}

double market::Supply::days_before_departure() const {
	return 20*std::exp(0.5*feature(days_before_departure_feature));
}

std::ostream& market::Supply::json(std::ostream& os, int indent) const {
	json::Object result;
	result.set("type", "Driver")
			.set("id", id())
			.set<json::Array>("features");
	for (int i=0; i<feature_dim; i++) {
		result.get<json::Array>("features").add(feature(i));
	}
	result.set("days_before_departure", days_before_departure());
	return result.json(os, indent);
}

double market::Demand::days_before_departure() const {
	return 15*std::exp(0.5*feature(days_before_departure_feature));
}

std::ostream& market::Demand::json(std::ostream& os, int indent) const {
	json::Object result;
	result.set("type", "Passenger")
		.set("id", id())
			.set<json::Array>("features");
	for (int i=0; i<feature_dim; i++) {
		result.get<json::Array>("features").add(feature(i));
	}
	result.set("days_before_departure", days_before_departure());
	return result.json(os, indent);
}

double market::Value::operator()(const Supply &d, const Demand &p) const {
	double result = 0;
	for (int i=0; i<feature_dim; i++) {
		for (int j=0; j<feature_dim; j++) {
			result += std::tanh(d.feature(i))*parameters_[feature_dim*i + j]*std::tanh(p.feature(j));
		}
	}
	return result;
}

std::ostream& market::Value::json(std::ostream& os, int indent) const {
	json::Object result;
	result.set("type", "Value")
			.set<json::Array>("parameters");
	for (int i=0; i<feature_dim; i++) {
		result.get<json::Array>("parameters")
				.add<json::Array>();
		for (int j=0; j<feature_dim; j++) {
			result.get<json::Array>("parameters")
					.get<json::Array>(i)
					.add(parameters_[feature_dim*i + j]);
		}
	}
	return result.json(os, indent);
}

void market::NormalValue::draw(Generator &generator) {
	std::normal_distribution<double> normal{};
	for (int i=0; i<feature_dim; i++) {
		for (int j=0; j<feature_dim; j++) {
			parameters_[feature_dim*i + j] = normal(generator);
		}
	}
}

void market::SoftValue::draw(Generator &generator) {
	std::normal_distribution<double> normal;
	for (int i=0; i<feature_dim; i++) {
		for (int j=0; j<feature_dim; j++) {
			parameters_[feature_dim*i + j] = 0.1*normal(generator);
		}
	}
	parameters_[0] = 2;
}

double market::Modifier::operator()(const Supply &s, const Demand &d, const Value &v) const {
	return v(s,d) + parameters_[demand_split_dim*(s.id() % supply_split_dim) + (d.id() % demand_split_dim)];
}

std::ostream& market::Modifier::json(std::ostream& os, int indent) const {
	json::Object result;
	result.set("type", "Modifier")
			.set<json::Array>("parameters");
	for (int i=0; i<supply_split_dim; i++) {
		result.get<json::Array>("parameters")
				.add<json::Array>();
		for (int j=0; j<demand_split_dim; j++) {
			result.get<json::Array>("parameters")
					.get<json::Array>(i)
					.add(parameters_[demand_split_dim*i + j]);
		}
	}
	return result.json(os, indent);
}

void market::TreatmentModifier::draw(Generator &generator) {
	std::bernoulli_distribution bernoulli(proba_);
	for (int i=0; i<supply_split_dim; i++) {
		for (int j=0; j<demand_split_dim; j++) {
			parameters_[demand_split_dim*i + j] = bernoulli(generator) ? impact_ : 0;
		}
	}
}

void market::SupplyTreatmentModifier::draw(Generator &generator) {
	std::bernoulli_distribution bernoulli(proba_);
	for (int i=0; i<supply_split_dim; i++) {
		double impact = bernoulli(generator) ? impact_ : 0;
		for (int j=0; j<demand_split_dim; j++) {
			parameters_[demand_split_dim*i + j] = impact;
		}
	}
}

void market::MatchingModifier::draw(Generator &generator) {
	std::bernoulli_distribution bernoulli(proba_);
	for (int i=0; i<supply_split_dim; i++) {
		for (int j=0; j<demand_split_dim; j++) {
			parameters_[demand_split_dim*i + j] = bernoulli(generator) ? impact_ : 0;
		}
	}
}
