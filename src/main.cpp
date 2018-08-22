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

#include "market/matching.h"
#include "market/treatment.h"
#include "market/market.h"
#include "market/value.h"
#include "utils/plot.h"

#include "tests.h"

using namespace std;
namespace b = boost;
//namespace r = ranges;

int main() {
	Tests tests;

	Market<StructuredNoisyValue, SplitTreatment, FullMatching> m(100, 100,
			StructuredNoisyValue(StructuredNoisyValue::basic_structure, 10, 10, 0, 0.5),
			SplitTreatment(0.5, 0.4, 1), FullMatching());

	m.solve();
	return 0;
}
