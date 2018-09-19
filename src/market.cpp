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
	// Add a constant
	parameters_[feature_dim*0 + 0] = 1;
}

void market::SoftValue::draw(Generator &generator) {
	std::normal_distribution<double> normal;
	for (int i=0; i<feature_dim; i++) {
		for (int j=0; j<feature_dim; j++) {
			parameters_[feature_dim*i + j] = 0.1*normal(generator);
		}
	}
	// Add a constant
	parameters_[feature_dim*0 + 0] = 1;
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

market::TreatmentModifier& market::TreatmentModifier::proba(double p) {
	proba_ = p;
	return *this;
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

market::SupplyTreatmentModifier& market::SupplyTreatmentModifier::proba(double p) {
	proba_ = p;
	return *this;
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

market::MatchingModifier& market::MatchingModifier::proba(double p) {
	proba_ = p;
	return *this;
}

std::ostream& market::Result::json(std::ostream& os, int indent) const {
	json::Object result;
	result.set("type", "Result")
		.set("sample_size", sample_size)
		.set("treated_share", treated_share)
		.set("gmv_mean", gmv_mean)
		.set("gmv_min", gmv_min)
		.set("gmv_low", gmv_low)
		.set("gmv_med", gmv_med)
		.set("gmv_high", gmv_high)
		.set("gmv_max", gmv_max);
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

void market::Experiment::reset() {
	supply_searching.clear();
	demand_searching.clear();
	supply_candidates.clear();
	demand_candidates.clear();
	// Fill-in supply and demand searching lists
	for (Supply &s : supply) {
		supply_searching.insert(&s);
	}
	for (Demand &d : demand) {
		demand_searching.insert(&d);
	}
}

void market::Experiment::demand_propose() {
	double max_value = 0;
	Supply* supply_max = nullptr;
	// Find the best remaining supply for each demand
	for (Demand* d : demand_searching) {
		max_value = 0;
		supply_max = nullptr;
		for (Supply* s : supply_searching) {
			double value = treatment(*s,*d,demand_value,1);
			if (value > max_value) {
				max_value = value;
				supply_max = s;
			}
		}
		if (max_value>0) {
			demand_candidates.insert(std::make_pair(d, SupplyValue(supply_max, max_value)));
			supply_candidates.insert(std::make_pair(supply_max, DemandValue(d, treatment(*supply_max,*d,supply_value,0.0))));
			match = true;
		}
	}
}

double market::Experiment::supply_dispose() {
	// We match the preferred
	double total_value = 0;
	double max_value = 0;
	Demand* demand_max = nullptr;
	Supply* current = nullptr;
	for (std::pair<Supply*, DemandValue> sdv : supply_candidates) {
		if (current != sdv.first) {
			if (max_value>0) {
				supply_candidates.erase(current);
				demand_candidates.erase(demand_max);
				supply_searching.erase(current);
				demand_searching.erase(demand_max);
				matched.insert(std::make_pair(current, demand_max));
				total_value += max_value;
			}
			current = sdv.first;
			max_value = 0;
			demand_max = nullptr;
		}
		if (sdv.second.value > max_value) {
			max_value = sdv.second.value;
			demand_max = sdv.second.demand;
			match = true;
		}
	}
	if (max_value>0) {
		supply_candidates.erase(current);
		demand_candidates.erase(demand_max);
		supply_searching.erase(current);
		demand_searching.erase(demand_max);
		matched.insert(std::make_pair(current, demand_max));
		total_value += max_value;
	}
	return total_value;
}

void market::Experiment::print() {
	std::cout << std::endl << "Market print" << std::endl;
	std::cout << std::endl << "Supply " << std::endl;
	for (Demand* d : demand_searching) {
		std::cout << d->id() << std::endl;
	}
	std::cout << std::endl << "Demand " << std::endl;
	for (Supply* s : supply_searching) {
		std::cout << s->id() << std::endl;
	}
}

market::Result market::Experiment::run(int sample_size, double treated_share) {
	treatment.proba(treated_share);
	// Declare result
	Result result;
	result.sample_size = sample_size;
	result.treated_share = treated_share;
	std::vector<double> gmvs;
	double gmvs_sum = 0;
	for (int i=0; i<sample_size; i++) {
		double gmv = 0;
		// Empty the maps for a new run
		reset();
		// Update omega
		++omega;
		// Iterate until no match is left
		match = true;
		for (int k=0; k<market_iterations && match; k++) {
			//std::cout << demand_searching.size() << " passengers left at iteration: " << k << std::endl;
			// Is there a match?
			match = false;
			demand_propose();
			gmv += supply_dispose();
		}
		//print();
		gmvs.push_back(gmv);
		gmvs_sum += gmv;
		//std::cout << "Run " << i+1 << "/" << sample_size << std::endl;
	}
	std::sort(gmvs.begin(), gmvs.end());
	result.gmv_min = gmvs[0];
	result.gmv_low = gmvs[gmvs.size()*1/4];
	result.gmv_med = gmvs[gmvs.size()*1/2];
	result.gmv_high = gmvs[gmvs.size()*3/4];
	result.gmv_max = gmvs[gmvs.size()-1];
	result.gmv_mean = gmvs_sum/gmvs.size();
	return result;
}


