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

class Demand {
private:
	unsigned long id_;
	int entry_;
public:
	static std::uniform_int_distribution<unsigned long> id_distrib;
	static std::geometric_distribution<int> entry_distrib;
	static const double expected_entry_days;
	unsigned long id() const;
	std::chrono::system_clock::time_point travel_date() const;
	std::chrono::system_clock::time_point enter_date() const;
	// Implement the requirement for Omega::Ext
	template <typename G> void random(G g) {
		id_ = id_distrib(g);
		entry_ = entry_distrib(g);
	}
	friend std::ostream& operator<<(std::ostream& os, const Demand& d);
};

#endif /* DEMAND_H_ */
