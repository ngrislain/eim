/*
 * main.cpp
 *
 *  Created on: 17 juil. 2018
 *      Author: ngrislain16
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <boost/process.hpp>
#include <boost/multi_array.hpp>
#include <range/v3/all.hpp>

#include "market/matching.h"
#include "market/supply.h"
#include "market/demand.h"
#include "utils/plot.h"

using namespace std;
namespace b = boost;
namespace r = ranges;

int main() {
	Plot p;

	Matching m = Matching(100, 100);
	m.split_matching(0.5);
	m.bernoulli_matching(0.5);

	//cout << m << endl;

	list<double> unif;
	for (int i=0; i<100; i++) {
		Demand d;
		unif.push_back(d.generator(0)());
		time_t enter = chrono::system_clock::to_time_t(d.enter_date);
		time_t travel = chrono::system_clock::to_time_t(d.travel_date);
		cout << d << endl;
	}

//	p.plot(array<double,7>{1,2,3,6,89,10,100});
	p.plot(unif, ", 'ro', alpha=0.2");
//	p.image(m.data());

	return 0;
}
