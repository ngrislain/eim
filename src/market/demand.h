/*
 * Demand.h
 *
 *  Created on: 7 août 2018
 *      Author: ngrislain16
 */

#ifndef DEMAND_H_
#define DEMAND_H_

#include <random>
#include <functional>
#include <chrono>

#include "../utils/omega.h"

class Demand {
private:
	// We hold a reference of the Omega::Ext object
	Omega::Ext<Demand> ext_;
	unsigned long id_;
	int entry_;
public:
	static std::uniform_int_distribution<unsigned long> id_distrib;
	static std::geometric_distribution<int> entry_distrib;
	static const double expected_entry_days;
	unsigned long id() const;
	Demand(Omega &o);
	std::chrono::system_clock::time_point travel_date() const;
	std::chrono::system_clock::time_point enter_date() const;
	// Implement the requirement for Omega::Ext
	template <typename G> void random(G g);
	friend std::ostream& operator<<(std::ostream& os, const Demand& d);
};

#endif /* DEMAND_H_ */
