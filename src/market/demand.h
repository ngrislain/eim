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
	double entry_;
	std::chrono::system_clock::time_point now_;
public:
	static std::uniform_int_distribution<unsigned long> id_distrib;
	static std::exponential_distribution<double> entry_distrib;
	Demand() : now_(std::chrono::system_clock::now()) {}
	unsigned long id() const;
	std::chrono::system_clock::time_point travel_date() const;
	std::chrono::system_clock::time_point enter_date() const;
	friend bool operator< (const Demand& a, const Demand& b) { return a.entry_ < b.entry_; }
	friend bool operator> (const Demand& a, const Demand& b) { return b < a; }
	friend bool operator<=(const Demand& a, const Demand& b) { return !(a > b); }
	friend bool operator>=(const Demand& a, const Demand& b) { return !(a < b); }
	friend std::ostream& operator<<(std::ostream& os, const Demand& d);

	// Implement the requirement for Omega::Ext
	template <typename G> void random(G &g) {
		id_ = id_distrib(g);
		entry_ = entry_distrib(g);
	}
};

#endif /* DEMAND_H_ */
