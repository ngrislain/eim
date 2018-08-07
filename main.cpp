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
#include <nlohmann/json.hpp>

#include <matplotlibcpp.h>

#include "Entity.h"
#include "Supply.h"
#include "Demand.h"
#include "matching.h"

using namespace std;
using namespace boost;
using namespace boost::process;
using namespace nlohmann;

namespace plt = matplotlibcpp;

int main() {

	list<double> unif { };
	for (int i = 0; i < 1000; i++) {
		Demand d;
		unif.push_back(d.rand());
	}
	json j = unif;
	// add an array that is stored as std::vector (using an initializer list)
	cout << j << endl;

	// Prepare data.
	int n = 5000;
	std::vector<double> x(n), y(n), z(n), w(n, 2);
	for (int i = 0; i < n; ++i) {
		x.at(i) = i * i;
		y.at(i) = sin(2 * M_PI * i / 360.0);
		z.at(i) = log(i);
	}

	// Set the size of output image = 1200x780 pixels
	plt::figure_size(1200, 780);
	// Plot line from given x and y data. Color is selected automatically.
	plt::plot(x, y);
	// Plot a red dashed line from given x and y data.
	plt::plot(x, w, "r--");
	// Plot a line whose name will show up as "log(x)" in the legend.
	plt::named_plot("log(x)", x, z);

	// Set x-axis to interval [0,1000000]
	plt::xlim(0, 1000 * 1000);
	// Enable legend.
	plt::legend();
	plt::show();
	// Save the image (file format is determined by the extension)
	plt::save("./basic.png");

	Matching m = Matching(10, 10);
	m.split_matching(0.5);
	m.bernoulli_matching(0.5);

	cout << m << endl;

	return 0;
}
