/*
 * Supply.cpp
 *
 *  Created on: 7 août 2018
 *      Author: ngrislain16
 */

#include "supply.h"

#include <iostream>
#include <ctime>
#include <iomanip>

#include "params.h"

using namespace std;
using namespace std::chrono;

std::uniform_int_distribution<unsigned long> Supply::id_distrib{};
std::geometric_distribution<int> Supply::entry_distrib{1/Params::supply_expected_entry_days};

unsigned long Supply::id() const {return id_;}

std::chrono::system_clock::time_point Supply::travel_date() const {
	return system_clock::now();
}

std::chrono::system_clock::time_point Supply::enter_date() const {
	return system_clock::now()-hours(24*entry_);
}

ostream& operator<<(ostream& os, const Supply& s){
	time_t travel = system_clock::to_time_t(s.travel_date());
	time_t enter = system_clock::to_time_t(s.enter_date());
	os << "Supply(travel=" << put_time(localtime(&travel), "%F") << ", enter=" << put_time(localtime(&enter), "%F") << ")";
	return os;
}
