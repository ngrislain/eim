/*
 * matching.cpp
 *
 *  Created on: 17 juil. 2018
 *      Author: ngrislain16
 */

#include <sstream>

#include "matching.h"

using namespace std;
using namespace boost;

Matching::Matching(int supply_size, int demand_size) : gen(0), id(gen()), data_(boost::extents[supply_size][demand_size]) {};

Matching& Matching::full() {
	for (Matching::IndexType i=0; i<data().shape()[0]; i++) {
		for (Matching::IndexType j=0; j<data().shape()[1]; j++) {
			data_[i][j] = 1;
		}
	}
	return *this;
};

Matching& Matching::split(double share) {
	for (Matching::IndexType i=0; i<data().shape()[0]; i++) {
		for (Matching::IndexType j=0; j<data().shape()[1]; j++) {
			data_[i][j] = ((i < share*data().shape()[0]) && (j < share*data().shape()[1])) || ((i >= share*data().shape()[0]) && (j >= share*data().shape()[1]));
		}
	}
	return *this;
};

Matching& Matching::bernoulli(double p) {
	std::bernoulli_distribution distrib(p);
	for (Matching::IndexType i=0; i<data().shape()[0]; i++) {
		for (Matching::IndexType j=0; j<data().shape()[1]; j++) {
			data_[i][j] = distrib(gen);
		}
	}
	return *this;
};

Matching::DataType Matching::data() const {
	return data_;
}

bool Matching::operator()(const Supply &s, const Demand &d) const {
	return data()[s.id % data().shape()[0]][d.id % data().shape()[1]];
}

ostream& operator<<(ostream& os, const Matching& m){
	os << "[[" << m.data_[0][0];
	for (multi_array<bool, 2>::index j=1; j<m.data().shape()[1]; j++) {
		os << ", " << m.data()[0][j];
	}
	os << "]";
	for (multi_array<bool, 2>::index i=1; i<m.data().shape()[0]; i++) {
		os << endl << " [" << m.data_[i][0];
		for (multi_array<bool, 2>::index j=1; j<m.data().shape()[1]; j++) {
			os << ", " << m.data()[i][j];
		}
		os << "]";
	}
	os << "]" << endl;
	return os;
}
