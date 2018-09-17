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
#include <map>
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

double market::Value::operator()(const Supply &s, const Demand &d) const {
	double result = 0;
	if (s.days_before_departure()>d.days_before_departure()) {
		for (int i=0; i<feature_dim; i++) {
			for (int j=0; j<feature_dim; j++) {
				result += std::tanh(s.feature(i))*parameters_[feature_dim*i + j]*std::tanh(d.feature(j));
			}
		}
	} else {
		result = -1;
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

double market::Modifier::operator()(const Supply &s, const Demand &d, const Value &v, double impact) const {
	double result;
	if (s.days_before_departure()>d.days_before_departure()) {
		result = v(s,d) + impact*parameters_[demand_split_dim*(s.id() % supply_split_dim) + (d.id() % demand_split_dim)];
	} else {
		result = -1;
	}
	return result;
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
			parameters_[demand_split_dim*i + j] = bernoulli(generator) ? 1 : 0;
		}
	}
}

void market::SupplyTreatmentModifier::draw(Generator &generator) {
	std::bernoulli_distribution bernoulli(proba_);
	for (int i=0; i<supply_split_dim; i++) {
		double treat = bernoulli(generator) ? 1 : 0;
		for (int j=0; j<demand_split_dim; j++) {
			parameters_[demand_split_dim*i + j] = treat;
		}
	}
}

void market::MatchingModifier::draw(Generator &generator) {
	std::bernoulli_distribution bernoulli(proba_);
	for (int i=0; i<supply_split_dim; i++) {
		for (int j=0; j<demand_split_dim; j++) {
			parameters_[demand_split_dim*i + j] = bernoulli(generator) ? 1 : 0;
		}
	}
}

double market::MatchingModifier::operator()(const Supply &s, const Demand &d, const Value &v) const {
	double result;
	if (s.days_before_departure()>d.days_before_departure() && parameters_[demand_split_dim*(s.id() % supply_split_dim) + (d.id() % demand_split_dim)]>0) {
		result = v(s,d);
	} else {
		result = -1;
	}
	return result;
}

std::ostream& market::Result::json(std::ostream& os, int indent) const {
	json::Object result;
	result.set("type", "Result").set("gmv", gmv);
	return result.json(os, indent);
}

std::ostream& market::SupplyValue::json(std::ostream& os, int indent) const {
	json::Object result;
	result.set("type", "Candidate").set("supply", supply->id()).set("value", value);
	return result.json(os, indent);
}

std::ostream& market::DemandValue::json(std::ostream& os, int indent) const {
	json::Object result;
	result.set("type", "Candidate").set("demand", demand->id()).set("value", value);
	return result.json(os, indent);
}

market::Experiment::Experiment() : omega(), long_term_omega(), supply_value(long_term_omega), demand_value(long_term_omega), treatment(long_term_omega) {
	// Create supply and demand
	for (int i=0; i<supply_dim; i++) {
		supply.push_back(Supply(omega));
	}
	for (int j=0; j<demand_dim; j++) {
		demand.push_back(Demand(omega));
	}
	std::cout << "Experiment created" << std::endl;
	std::cout << omega << std::endl;
	++long_term_omega;
}

market::Result market::Experiment::run() {
	// Update omega
	++omega;
	// Declare result
	Result result(0);
	// Create maps for book-keeping;
	std::multimap<Supply*, DemandValue> supply_candidates;
	std::multimap<Demand*, SupplyValue> demand_candidates;
	std::map<Supply*, Demand*> matched;
	// Fill-in supply and demand
	for (Supply &s : supply) {
		supply_candidates.insert(std::make_pair(&s, DemandValue(nullptr, -1)));
	}
	for (Demand &d : demand) {
		demand_candidates.insert(std::make_pair(&d, SupplyValue(nullptr, -1)));
	}
	// Iterate until no-one is left
	for (int k=0; k<1; k++) {
		double max_value = 0;
		Supply* supply_max = nullptr;
		Demand* demand_max = nullptr;
		Supply* current = nullptr;
		// Find the best remaining supply for each demand
		for (Demand &d : demand) {
			max_value = 0;
			supply_max = nullptr;
			for (Supply &s : supply) {
				double value = treatment(s,d,demand_value,0.1);
				if (value > max_value) {
					max_value = value;
					supply_max = &s;
				}
			}
			if (max_value>0) {
				demand_candidates.erase(&d);
				demand_candidates.insert(std::make_pair(&d, SupplyValue(supply_max, max_value)));
				supply_candidates.insert(std::make_pair(supply_max, DemandValue(&d, treatment(*supply_max,d,supply_value,0))));
			}
		}
		// We match the preferred
		max_value = 0;
		demand_max = nullptr;
		for (std::pair<Supply*, DemandValue> kv : supply_candidates) {
			if (current != kv.first) {
				if (max_value>0) {
					supply_candidates.erase(kv.first);
					demand_candidates.erase(kv.second.demand);
					matched.insert(std::make_pair(kv.first, kv.second.demand));
				}
				current = kv.first;
				max_value = 0;
				demand_max = nullptr;
			}
			if (kv.second.value > max_value) {
				max_value = kv.second.value;
				demand_max = kv.second.demand;
			}
		}

		std::cout << std::endl << "Supply " << std::endl;
		for (std::pair<Supply*, DemandValue> kv : supply_candidates) {
			std::cout << kv.first->id() << ": " << ((kv.second.value>0)?kv.second.demand->id():0) << ", " << kv.second.value << std::endl;
		}
		std::cout << std::endl << "Demand " << std::endl;
		for (std::pair<Demand*, SupplyValue> kv : demand_candidates) {
			std::cout << kv.first->id() << ": " << ((kv.second.value>0)?kv.second.supply->id():0) << ", " << kv.second.value << std::endl;
		}
	}
	return result;
}


