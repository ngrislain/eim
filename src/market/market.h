/*
 * market.h
 *
 *  Created on: 21 août 2018
 *      Author: ngrislain16
 */

#ifndef MARKET_MARKET_H_
#define MARKET_MARKET_H_

#include <vector>
#include <queue>
#include <set>
#include "supply.h"
#include "demand.h"
#include "../utils/omega.h"

template <typename Value, typename Treatment, typename Matching>
class Market {
private:
	Omega omega_;
	// Supply vector
	std::vector<Omega::Ext<Supply>> supply_vector_;
	// Demand vector
	std::vector<Omega::Ext<Demand>> demand_vector_;
	// Comparator for Demand
	class DemandCompare {
	public:
		constexpr bool operator()(const Demand* a, const Demand* b) const {return a->enter_date() > b->enter_date();}
	};
	// Demand to be satisfied
	std::priority_queue<Demand*, std::vector<Demand*>, DemandCompare> demand_to_satisfy_;
	// Supply to allocate
	std::set<Supply*> supply_to_allocate_;
	// Value matrix
	Omega::Ext<Value> value_;
	// Treatment matrix
	Omega::Ext<Treatment> treatment_;
	// Matching matrix
	Omega::Ext<Matching> matching_;
public:
	Market(int supply_size, int demand_size, Value &&v, Treatment &&t, Matching &&m) : value_(omega_(std::move(v))),
			treatment_(omega_(std::move(t))), matching_(omega_(std::move(m))) {
		for (int k = 0; k < supply_size; k++) {
			supply_vector_.push_back(omega_(Supply()));
		}
		for (int k = 0; k < demand_size; k++) {
			demand_vector_.push_back(omega_(Demand()));
		}
	}

	void solve() {
		for (Omega::Ext<Demand> &d : demand_vector_) {
			demand_to_satisfy_.push(&(d()));
		}
		while (!demand_to_satisfy_.empty()) {
			Demand *d = demand_to_satisfy_.top();
			std::cout << *d << std::endl;
			demand_to_satisfy_.pop();
		}
	}
};

#endif /* MARKET_MARKET_H_ */
