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

#include "tests.h"
#include "market/matching.h"
#include "market/supply.h"
#include "market/demand.h"
#include "utils/plot.h"

using namespace std;
namespace b = boost;
namespace r = ranges;

int main() {
	Tests tests;

	Plot p;

	Matching m = Matching(10, 10).bernoulli(0.5);
	cout << m << endl;

	list<double> x, y;
	Demand d;
	for (int i=0; i<10000; i++) {
		d.init();
		time_t enter = chrono::system_clock::to_time_t(d.enter_date());
		time_t travel = chrono::system_clock::to_time_t(d.travel_date());
		x.push_back(enter);
		y.push_back(d.d_gen("y")());
	}
	//    p.plot(x, y, ", 'ro', alpha=0.5");

	array<Supply,100> ss;
	array<Demand,100> ds;
	b::multi_array<bool, 2> a(b::extents[100][100]);
	for (int i=0; i<ss.size(); i++)
		for (int j=0; j<ds.size(); j++) {
			a[i][j] = m(ss[i], ds[j]);
		}

	//p.image(a);

	return 0;
}
