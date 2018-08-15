/*
 * value.h
 *
 *  Created on: 14 août 2018
 *      Author: ngrislain16
 */

#ifndef MARKET_VALUE_H_
#define MARKET_VALUE_H_

#include <iostream>
#include <string>
#include <boost/multi_array.hpp>
#include "supply.h"
#include "demand.h"
#include "../utils/omega.h"

class Value {
private:
	typedef boost::multi_array<double, 2> DataType;
	typedef DataType::index IndexType;
	DataType data_;
	double mu_;
	double sigma_;
	std::mt19937_64 gen;
public:
	Value(int supply_size, int demand_size, double mu, double sigma);
	unsigned long id;
	Value& init();
	DataType data() const;
	double operator()(const Supply &s, const Demand &d);
	friend std::ostream& operator<<(std::ostream& os, const Value& matching);
private:
	std::normal_distribution<double> distrib_;
};

#endif /* MARKET_VALUE_H_ */
