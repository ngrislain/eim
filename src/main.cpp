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
#include "utils/vector.h"
#include "utils/plot.h"

using namespace std;
using namespace boost;

int main() {
	Plot p;

	Matching m = Matching(10, 10);
	m.split_matching(0.5);
	m.bernoulli_matching(0.5);

	cout << m << endl;

	// Create a 3D array that is 3 x 4 x 2
	multi_array<double,2> A(boost::extents[3][4]);

	// Assign values to the elements
	int values = 0;
	for (multi_array<double,2>::index i = 0; i != 3; ++i)
		for (multi_array<double,2>::index j = 0; j != 4; ++j)
			A[i][j] = values++;

	Vector<std::array<int,2>,double,multi_array<double,2>> V(A);

	//p.image(m.matrix);

	return 0;
}
