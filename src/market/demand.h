/*
 * Demand.h
 *
 *  Created on: 7 août 2018
 *      Author: ngrislain16
 */

#ifndef DEMAND_H_
#define DEMAND_H_

#include <random>
#include <chrono>

class Demand {
private:
	unsigned long id_;
	int entry_;
public:
	static std::uniform_int_distribution<unsigned long> id_distrib;
	static std::geometric_distribution<int> entry_distrib;
	unsigned long id() const;
	std::chrono::system_clock::time_point travel_date() const;
	std::chrono::system_clock::time_point enter_date() const;
	friend std::ostream& operator<<(std::ostream& os, const Demand& d);

	// Implement the requirement for Omega::Ext
	template <typename G> void random(G g) {
		id_ = id_distrib(g);
		entry_ = entry_distrib(g);
	}
};

#endif /* DEMAND_H_ */
