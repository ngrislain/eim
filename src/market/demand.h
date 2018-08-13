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
	DeterministicGenerator entry_gen_;
	std::chrono::system_clock::time_point travel_date_;
	std::chrono::system_clock::time_point enter_date_;
public:
	static const double expected_entry_days;
	static std::exponential_distribution<double> entry_distrib;
	Demand();
	Demand& init();
	std::chrono::system_clock::time_point travel_date() const;
	std::chrono::system_clock::time_point enter_date() const;
	friend std::ostream& operator<<(std::ostream& os, const Demand& d);
};

#endif /* DEMAND_H_ */
