/*
 * main.cpp
 *
 *  Created on: 17 juil. 2018
 *      Author: ngrislain16
 */
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>
#include <iomanip>
#include <boost/process.hpp>
#include <boost/multi_array.hpp>
#include "market_v0/market.h"
#include "market_v0/matching.h"
#include "market_v0/treatment.h"
#include "market_v0/value.h"
//#include <nlohmann/json.hpp>

#include "tests.h"
#include "utils_v0/plot.h"

using namespace std;
namespace b = boost;
//namespace r = ranges;

int main() {
	Tests tests;

	std::vector<Metrics> metrics;

	// Test a simple market
	Market<StructuredNoisyValue, SplitTreatment, FullMatching> m(500, 500,
				StructuredNoisyValue(StructuredNoisyValue::basic_structure, 10, 10, 0, 1),
				SplitTreatment(0.5, 0.5, 1),
				FullMatching());

	// Test markets with varying exposure rates but no matching function
	metrics.clear();
	for (int i=0; i<=50; i++) {
		double p = 10*i/50.;
		double mean = 5/(5+p);
		cout << "Distribution mean = " << mean << endl;

		Market<StructuredNoisyValue, CompoundBernoulliTreatment, FullMatching> m(500, 500,
						StructuredNoisyValue(StructuredNoisyValue::basic_structure, 100, 100, 0, 2),
						CompoundBernoulliTreatment(0.1, 5, p, 100, 100),
						FullMatching());

		for (int j=0; j<100; j++) {
			metrics.push_back(m.resolve());
			metrics.back().parameter = mean;
		}
	}

	cout << "Writing output to: /tmp/output.json" << endl;
	ofstream output;
	output.open ("/tmp/output.json");
	output << "[" << metrics[0];
	for (int k=1; k<metrics.size(); k++) {
		output << ", " << metrics[k] << endl;
	}
	output << "]" << endl;
	output.close();
	cout << "Done" << endl;
	return 0;
}
