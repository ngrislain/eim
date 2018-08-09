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
#include <boost/process.hpp>
#include <boost/multi_array.hpp>

#include "demand.h"
#include "entity.h"

#include "matching.h"
#include "supply.h"
#include "utils/for.h"
#include "utils/vector.h"
#include "utils/plot.h"

using namespace std;
namespace b = boost;

int main() {
	Plot p;

	Matching m = Matching(100, 100);
	m.split_matching(0.5);
	m.bernoulli_matching(0.5);

	//cout << m << endl;

//	Vector<std::array<int, 2>, double, boost::multi_array<bool, 2>> V(m.data());
//	V.for_each([](array<int,2> k, double v){cout << v << ", ";});

//	For<b::multi_array<bool, 2>, array<int,2>, double>::each(m.data(), [](array<int,2> k, double v){cout << k[0] << ", " << k[1] << " : " << v << endl;});
//
//	cout << For<b::multi_array<bool, 2>, array<int,2>, double>::one(m.data(), array<int,2>{1,1}) << endl;
//
//	For<array<double, 5>, int, double>::each(array<double, 5>{1,2,3,4,5}, [](int k, double v){cout << k << " : " << v << endl;});
//
//	cout << For<array<double, 5>, int, double>::one(array<double, 5>{1,2,3,4,5}, 1) << endl;

	p.image(m.data());

	return 0;
}
