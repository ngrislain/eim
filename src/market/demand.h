/*
 * Demand.h
 *
 *  Created on: 7 août 2018
 *      Author: ngrislain16
 */

#ifndef DEMAND_H_
#define DEMAND_H_

#include "entity.h"

#include <chrono>

class Demand : public Entity {
private:
	DeterministicGenerator entry_gen;
public:
	static constexpr double expected_entry_day = 10;
	static std::exponential_distribution<double> entry_distrib;
	std::chrono::system_clock::time_point travel_date;
	std::chrono::system_clock::time_point enter_date;
	Demand();
	friend std::ostream& operator<<(std::ostream& os, const Demand& d);
};

#endif /* DEMAND_H_ */
