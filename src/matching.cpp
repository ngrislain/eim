/*
 * matching.cpp
 *
 *  Created on: 17 juil. 2018
 *      Author: ngrislain16
 */

#include <sstream>
#include <time.h>

#include "matching.h"

using namespace std;
using namespace boost;

Matching::Matching(int supply_size, int demand_size) : supply_size(supply_size),
		demand_size(demand_size),
		matrix(extents[supply_size][demand_size]) {
	random_number_generator.seed(time(0));
}

Matching& Matching::full_matching() {
	for (multi_array<bool, 2>::index i=0; i<supply_size; i++) {
		for (multi_array<bool, 2>::index j=0; j<demand_size; j++) {
			matrix[i][j] = 1;
		}
	}
	return *this;
}

Matching& Matching::split_matching(float share) {
	for (multi_array<bool, 2>::index i=0; i<supply_size; i++) {
		for (multi_array<bool, 2>::index j=0; j<demand_size; j++) {
			matrix[i][j] = ((i < share*supply_size) && (j < share*demand_size)) || ((i >= share*supply_size) && (j >= share*demand_size));
		}
	}
	return *this;
}

Matching& Matching::bernoulli_matching(float p) {
	bernoulli_distribution<float> bernoulli = bernoulli_distribution<float>(p);
	for (multi_array<bool, 2>::index i=0; i<supply_size; i++) {
		for (multi_array<bool, 2>::index j=0; j<demand_size; j++) {
			matrix[i][j] = bernoulli(random_number_generator);
		}
	}
	return *this;
}

boost::multi_array<bool, 2> Matching::data() {
	return matrix;
}

ostream& operator<<(ostream& os, const Matching& matching){
	os << "[[" << matching.matrix[0][0];
	for (multi_array<bool, 2>::index j=1; j<matching.demand_size; j++) {
		os << ", " << matching.matrix[0][j];
	}
	os << "]";
	for (multi_array<bool, 2>::index i=1; i<matching.supply_size; i++) {
		os << endl << " [" << matching.matrix[i][0];
		for (multi_array<bool, 2>::index j=1; j<matching.demand_size; j++) {
			os << ", " << matching.matrix[i][j];
		}
		os << "]";
	}
	os << "]" << endl;
	return os;
}
