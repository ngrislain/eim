/*
 * Supply.h
 *
 *  Created on: 7 août 2018
 *      Author: ngrislain16
 */

#ifndef SUPPLY_H_
#define SUPPLY_H_

#include <random>
#include <functional>
#include <chrono>

#include "../utils/omega.h"

class Supply {
public:
	static const double expected_entry_days;
	Omega::Var<std::uniform_int_distribution<unsigned long>> id;
	Omega::Var<std::geometric_distribution<int>> entry;
	Supply(Omega &o);
	std::chrono::system_clock::time_point travel_date() const;
	std::chrono::system_clock::time_point enter_date() const;
	friend std::ostream& operator<<(std::ostream& os, const Supply& d);
};

#endif /* SUPPLY_H_ */
