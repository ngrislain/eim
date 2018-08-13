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

const double Demand::expected_entry_days = 5;
std::exponential_distribution<double> Demand::entry_distrib{1/Demand::expected_entry_days};

Demand::Demand() : entry_gen_(d_gen(0)) {
	travel_date_ = system_clock::now();
	enter_date_ = system_clock::now()-hours(24*(int)entry_distrib(entry_gen_));
}

Demand& Demand::init() {
	Entity::init();
	entry_gen_ = d_gen(0);
	travel_date_ = system_clock::now();
	enter_date_ = system_clock::now()-hours(24*(int)entry_distrib(entry_gen_));
	return *this;
}

std::chrono::system_clock::time_point Demand::travel_date() const {
	return travel_date_;
}

std::chrono::system_clock::time_point Demand::enter_date() const {
	return enter_date_;
}

ostream& operator<<(ostream& os, const Demand& d){
	time_t travel = system_clock::to_time_t(d.travel_date_);
	time_t enter = system_clock::to_time_t(d.enter_date_);
	os << "Demand(travel=" << put_time(localtime(&travel), "%F") << ", enter=" << put_time(localtime(&enter), "%F") << ")";
	return os;
}
