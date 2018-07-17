/*
 * main.cpp
 *
 *  Created on: 17 juil. 2018
 *      Author: ngrislain16
 */
#include <iostream>
#include <boost/process.hpp>
#include <boost/multi_array.hpp>

#include "matching.h"

using namespace std;
using namespace boost::process;
using namespace boost;

int main() {
	cout << "Running matplotlib" << endl;

	Matching m = Matching(10, 10);
	m.split_matching(0.5);
	m.bernoulli_matching(0.5);

	cout << m << endl;

	return 0;
}
