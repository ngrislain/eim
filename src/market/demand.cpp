/*
 * Demand.cpp
 *
 *  Created on: 7 août 2018
 *      Author: ngrislain16
 */

#include "demand.h"

#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;
using namespace std::chrono;

std::uniform_int_distribution<unsigned long> Demand::id_distrib{};
std::geometric_distribution<int> Demand::entry_distrib{};
const double Demand::expected_entry_days = 5;

Demand::Demand(Omega &o) {
	ext_ = o.ext(*this);
}

unsigned long Demand::id() const {
	return id_;
}

std::chrono::system_clock::time_point Demand::travel_date() const {
	return system_clock::now();
}

std::chrono::system_clock::time_point Demand::enter_date() const {
	return system_clock::now()-hours(24*entry_);
}

template <typename G> void Demand::random(G g) {
	std::cout << "DEBUG Demand::random" << std::endl;
	id_ = id_distrib(g);
	entry_ = entry_distrib(g);
	std::cout << "DEBUG Demand::random" << std::endl;
}

ostream& operator<<(ostream& os, const Demand& d){
	time_t travel = system_clock::to_time_t(d.travel_date());
	time_t enter = system_clock::to_time_t(d.enter_date());
	os << "Demand(travel=" << put_time(localtime(&travel), "%F") << ", enter=" << put_time(localtime(&enter), "%F") << ")";
	return os;
}
