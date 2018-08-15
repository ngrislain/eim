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
	std::mt19937_64 gen;
public:
	static const double expected_entry_days;
	unsigned long id;
	Demand();
	int entry() const;
	std::chrono::system_clock::time_point travel_date() const;
	std::chrono::system_clock::time_point enter_date() const;
	friend std::ostream& operator<<(std::ostream& os, const Demand& d);
};

#endif /* DEMAND_H_ */
