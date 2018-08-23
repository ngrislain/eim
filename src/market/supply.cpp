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
std::exponential_distribution<double> Supply::entry_distrib{1/Params::supply_expected_entry_days};

unsigned long Supply::id() const {return id_;}

std::chrono::system_clock::time_point Supply::travel_date() const {
	return now_;
}

std::chrono::system_clock::time_point Supply::enter_date() const {
	return now_-std::chrono::seconds((int)(24*3600*entry_));
}

ostream& operator<<(ostream& os, const Supply& s){
	time_t travel = system_clock::to_time_t(s.travel_date());
	time_t enter = system_clock::to_time_t(s.enter_date());
	os << "Supply(travel=" << put_time(localtime(&travel), "%F") << ", enter=" << put_time(localtime(&enter), "%F") << ")";
	return os;
}
