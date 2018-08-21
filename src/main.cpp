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

#include "tests.h"
//#include "market/matching.h"
//#include "market/value.h"
//#include "market/supply.h"
//#include "market/demand.h"
#include "utils/plot.h"

using namespace std;
namespace b = boost;
//namespace r = ranges;

int main() {
	Tests tests;
//
//	Plot p;
//
//	Matching m = Matching(10, 10).bernoulli(0.5);
//	cout << m << endl;
//
//
//	array<Supply, 100> ss;
//	array<Demand, 100> ds;
//	b::multi_array<double, 2> a(b::extents[100][100]);
//	for (int i = 0; i < ss.size(); i++) {
//		for (int j = 0; j < ds.size(); j++) {
//			a[i][j] = m(ss[i], ds[j]);
//		}
//	}
//
//	p.image(a);
//
//	Value v = Value(4, 4, 0, 0.1).init();
//	cout << v << endl;
//	for (int i = 0; i < ss.size(); i++) {
//		for (int j = 0; j < ds.size(); j++) {
//			a[i][j] = v(ss[i], ds[j]);
//		}
//	}
//	p.image(a);
//	for (int i=0; i<ss.size(); i++) {
//		for (int j=0; j<ds.size(); j++) {
//			a[i][j] = v(ss[i], ds[j]);
//		}
//	}
//	p.image(a);

	return 0;
}
