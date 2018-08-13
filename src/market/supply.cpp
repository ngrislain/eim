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

using namespace std;
using namespace std::chrono;

const double Supply::expected_entry_days = 10;
std::exponential_distribution<double> Supply::entry_distrib{1/Supply::expected_entry_days};

Supply::Supply() : entry_gen(d_gen(0)) {
	travel_date_ = system_clock::now();
	enter_date_ = system_clock::now()-hours(24*(int)entry_distrib(entry_gen));
}

Supply& Supply::init() {
	Entity::init();
	entry_gen = d_gen(0);
	travel_date_ = system_clock::now();
	enter_date_ = system_clock::now()-hours(24*(int)entry_distrib(entry_gen));
	return *this;
}

std::chrono::system_clock::time_point Supply::travel_date() const {
	return travel_date_;
}

std::chrono::system_clock::time_point Supply::enter_date() const {
	return enter_date_;
}

ostream& operator<<(ostream& os, const Supply& s){
	time_t travel = system_clock::to_time_t(s.travel_date_);
	time_t enter = system_clock::to_time_t(s.enter_date_);
	os << "Supply(travel=" << put_time(localtime(&travel), "%F") << ", enter=" << put_time(localtime(&enter), "%F") << ")";
	return os;
}
