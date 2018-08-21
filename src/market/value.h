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

class Value {
private:
	typedef boost::multi_array<double, 2> DataType;
	typedef DataType::index IndexType;
	std::normal_distribution<double> distrib_;
	DataType structure_;
	DataType noise_;
public:
	Value(DataType structure, int supply_size, int demand_size, double mu, double sigma) :
		structure_(structure), noise_(boost::extents[supply_size][demand_size]), distrib_(mu, sigma) {}
	inline double operator()(const Supply &s, const Demand &d) {
		return structure_[s.id() % structure_.shape()[0]][d.id() % structure_.shape()[1]] +
				noise_[s.id() % noise_.shape()[0]][d.id() % noise_.shape()[1]];
	}
	friend std::ostream& operator<<(std::ostream& os, const Value& v) {return os << "Value(" << v.noise_.shape()[0] << ", " << v.noise_.shape()[1] << ")";}

	// Required for Omega::Ext
	template <typename G> void random(G &g) {
		for (IndexType i=0; i<noise_.shape()[0]; i++) {
			for (IndexType j=0; j<noise_.shape()[1]; j++) {
				noise_[i][j] = distrib_(g);
			}
		}
	}

	// Some helpers
	static const DataType basic_structure;
};

#endif /* MARKET_VALUE_H_ */
