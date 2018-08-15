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

Demand::Demand() : gen(0), id(gen()) {}

int Demand::entry() const {
	return 0;
}

std::chrono::system_clock::time_point Demand::travel_date() const {
	return system_clock::now();
}

std::chrono::system_clock::time_point Demand::enter_date() const {
	return system_clock::now()-hours(24*entry());
}

ostream& operator<<(ostream& os, const Demand& d){
	time_t travel = system_clock::to_time_t(d.travel_date());
	time_t enter = system_clock::to_time_t(d.enter_date());
	os << "Demand(travel=" << put_time(localtime(&travel), "%F") << ", enter=" << put_time(localtime(&enter), "%F") << ")";
	return os;
}
