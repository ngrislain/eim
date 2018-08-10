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

std::exponential_distribution<double> Demand::entry_distrib{1/Demand::expected_entry_day};

Demand::Demand() : entry_gen(generator(0)) {
	travel_date = system_clock::now();
	cout << entry_distrib(entry_gen) << endl;
	cout << entry_gen() << endl;
	enter_date = system_clock::now()-hours(24*(int)entry_distrib(entry_gen));
}

ostream& operator<<(ostream& os, const Demand& d){
	time_t travel = system_clock::to_time_t(d.travel_date);
	time_t enter = system_clock::to_time_t(d.enter_date);
	os << "Demand(travel=" << put_time(localtime(&travel), "%F") << ", enter=" << put_time(localtime(&enter), "%F") << ")" << endl;
	return os;
}
