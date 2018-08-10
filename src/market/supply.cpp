/*
 * Supply.cpp
 *
 *  Created on: 7 août 2018
 *      Author: ngrislain16
 */

#include "supply.h"

using namespace std::chrono;

Supply::Supply() {
	travel_date = system_clock::now();
	enter_date = system_clock::now()-hours(24*10);
}
