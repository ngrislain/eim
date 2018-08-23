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

#include "params.h"

using namespace std;
using namespace std::chrono;

std::uniform_int_distribution<unsigned long> Demand::id_distrib{};
std::exponential_distribution<double> Demand::entry_distrib{1/Params::demand_expected_entry_days};

unsigned long Demand::id() const {return id_;}

std::chrono::system_clock::time_point Demand::travel_date() const {
	return now_;
}

std::chrono::system_clock::time_point Demand::enter_date() const {
	return now_-std::chrono::seconds((int)(24*3600*entry_));
}

ostream& operator<<(ostream& os, const Demand& d){
	time_t travel = system_clock::to_time_t(d.travel_date());
	time_t enter = system_clock::to_time_t(d.enter_date());
	os << "Demand(travel=" << put_time(localtime(&travel), "%F") << ", enter=" << put_time(localtime(&enter), "%F") << ")";
	return os;
}
