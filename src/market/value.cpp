/*
 * value.cpp
 *
 *  Created on: 14 août 2018
 *      Author: ngrislain16
 */

#include "value.h"

#include <sstream>


using namespace std;
using namespace boost;

Value::Value(int supply_size, int demand_size, double mu, double sigma) : gen(0), id(gen()), data_(boost::extents[supply_size][demand_size]),
		mu_(mu), sigma_(sigma), distrib_(mu_, sigma_) {};

Value& Value::init() {
	std::normal_distribution<double> distrib(0,1);
	for (Value::IndexType i=0; i<data().shape()[0]; i++) {
		for (Value::IndexType j=0; j<data().shape()[1]; j++) {
			data_[i][j] = distrib(gen);
		}
	}
	return *this;
};

Value::DataType Value::data() const {
	return data_;
}

double Value::operator()(const Supply &s, const Demand &d) {
	return data()[s.id() % data().shape()[0]][d.id() % data().shape()[1]] + distrib_(gen);
}

ostream& operator<<(ostream& os, const Value& v){
	os << "[[" << v.data_[0][0];
	for (multi_array<double, 2>::index j=1; j<v.data().shape()[1]; j++) {
		os << ", " << v.data()[0][j];
	}
	os << "]";
	for (multi_array<double, 2>::index i=1; i<v.data().shape()[0]; i++) {
		os << endl << " [" << v.data_[i][0];
		for (multi_array<double, 2>::index j=1; j<v.data().shape()[1]; j++) {
			os << ", " << v.data()[i][j];
		}
		os << "]";
	}
	os << "]" << endl;
	return os;
}
