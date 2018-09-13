/*
 * market.h
 *
 *  Created on: 21 août 2018
 *      Author: ngrislain16
 */

#ifndef MARKET_V0_MARKET_H_
#define MARKET_V0_MARKET_H_

#include <vector>
#include <queue>
#include <set>

#include "../market_v0/demand.h"
#include "../market_v0/supply.h"
#include "../utils_v0/omega.h"

//#define MARKET_DEBUG_

// Structure for resolution results
struct Metrics {
	double parameter;
	int total = 0;
	int treated = 0; // subset
	double treatment = 0;
	double value = 0;
	double treatment_x_treatment = 0;
	double value_x_value = 0;
	double treated_x_treatment = 0;
	double treated_x_value = 0;
	double treatment_x_value = 0;
	// Metrics to control the value
	double control = 0;
	double control_x_control = 0;
	double control_x_value = 0;
	double control_x_treated = 0;
	double control_x_treated_x_value = 0;
	friend std::ostream& operator<<(std::ostream& os, const Metrics& m) {
		return os << "{\"parameter\":"			<< m.parameter << "," << std::endl
				<< "\"total\":"					<< m.total << "," << std::endl
				<< "\"treated\":"				<< m.treated << "," << std::endl
				<< "\"treatment\":" 			<< m.treatment << "," << std::endl
				<< "\"value\":" 				<< m.value << "," << std::endl
				<< "\"treatment_x_treatment\":"	<< m.treatment_x_treatment << "," << std::endl
				<< "\"value_x_value\":"			<< m.value_x_value << "," << std::endl
				<< "\"treated_x_treatment\":"	<< m.treated_x_treatment << "," << std::endl
				<< "\"treated_x_value\":"		<< m.treated_x_value << "," << std::endl
				<< "\"treatment_x_value\":"		<< m.treatment_x_value << "," << std::endl
				<< "\"control\":"				<< m.control << "," << std::endl
				<< "\"control_x_control\":"		<< m.control_x_control << "," << std::endl
				<< "\"control_x_value\":"		<< m.control_x_value << "," << std::endl
				<< "\"control_x_treated\":"		<< m.control_x_treated << "," << std::endl
				<< "\"control_x_treated_x_value\":"	<< m.control_x_treated_x_value << "}";
	}
};

template <typename Value, typename Treatment, typename Matching>
class Market {
private:
	Omega omega_;
	// Supply vector
	std::vector<Omega::Ext<Supply>> supply_vector_;
	// Demand vector
	std::vector<Omega::Ext<Demand>> demand_vector_;
	// Comparator for Supply
	class SupplyCompare {
	public:
		constexpr bool operator()(const Supply* a, const Supply* b) const {return (*a) > (*b);}
	};
	// Comparator for Demand
	class DemandCompare {
	public:
		constexpr bool operator()(const Demand* a, const Demand* b) const {return (*a) > (*b);}
	};
	// Demand to be satisfied
	std::priority_queue<Demand*, std::vector<Demand*>, DemandCompare> demand_to_satisfy_;
	// Supply to allocate
	std::set<Supply*, SupplyCompare> supply_to_allocate_;
	// Value matrix
	Omega::Ext<Value> value_;
	// Treatment matrix
	Omega::Ext<Treatment> treatment_;
	// Matching matrix
	Omega::Ext<Matching> matching_;
public:
	// Initiate all structures
	Market(int supply_size, int demand_size, Value &&v, Treatment &&t, Matching &&m) : omega_(10), value_(omega_(std::move(v))),
			treatment_(omega_(std::move(t))), matching_(omega_(std::move(m))) {
		for (int k = 0; k < supply_size; k++) {
			supply_vector_.push_back(omega_(Supply()));
		}
		for (int k = 0; k < demand_size; k++) {
			demand_vector_.push_back(omega_(Demand()));
		}
#ifdef MARKET_DEBUG_
		std::cout << "First supply element " << supply_vector_[0]().id() << std::endl;
		std::cout << "First demand element " << demand_vector_[0]().id() << std::endl;
#endif
	}
	// Resolve the market
	Metrics resolve() {
		Metrics result;
		Demand *d;
		bool treated;
		double treatment;
		double value;
		double control;
		Supply *arg_max;
		bool max_treated;
		double max_treatment;
		double max_value;
		double max_control;
		// Fill-in supply to allocate
		supply_to_allocate_.clear();
		for (Omega::Ext<Supply> &s : supply_vector_) {
			supply_to_allocate_.insert(&(s()));
		}
		// Sort demand to satisfy
		for (Omega::Ext<Demand> &d : demand_vector_) {
			demand_to_satisfy_.push(&(d()));
		}
		// Go through all demand by growing entry dates
		while (!demand_to_satisfy_.empty()) {
			d = demand_to_satisfy_.top();
			treated = false;
			treatment = 1;
			value = 0;
			control = treatment_().marginal(*d);
			arg_max = nullptr;
			max_treated = false;
			max_treatment = 1;
			max_value = 0;
			for (Supply *s : supply_to_allocate_) {
				value = 0;
				if (s->enter_date()<d->enter_date()) { // Pair available
					// Update some metrics
					treated = treatment_()(*s, *d) != 1;
					treatment = treatment_()(*s, *d);
					result.total += 1; // One more pair tried
					result.treated += treated; // One more treated ?
					result.treatment += treatment; // Cumulate treatment
					result.treatment_x_treatment += treatment*treatment;
					result.treated_x_treatment += treated*treatment;
					result.control += control;
					result.control_x_control += control*control;
					result.control_x_treated += control*treated;
					// Then if matching there is a potential match
					if (matching_()(*s, *d)) {// Pair is matched
						value = value_()(*s, *d) * treatment_()(*s, *d);
						if (value > max_value) {
							max_treated = treated;
							max_treatment = treatment;
							max_value = value;
							max_control = control;
							arg_max = s;
						}
					}
				}
			}
			// Remove supply from available supply
			if (arg_max != nullptr) {
				supply_to_allocate_.erase(arg_max);
				result.value += max_value;
				result.value_x_value += max_value*max_value;
				result.treated_x_value += max_treated*max_value;
				result.treatment_x_value += max_treatment*max_value;
				result.control_x_value += max_control*max_value;
				result.control_x_treated_x_value += max_control*max_treated*max_value;
			}
			// Remove demand to process
			demand_to_satisfy_.pop();
			// Add generated value to GMV
		}
		// Update the source of noise
		++omega_;
		// Return the result
		return result;
	}
};

#endif /* MARKET_V0_MARKET_H_ */
