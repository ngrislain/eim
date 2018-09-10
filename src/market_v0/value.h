/*
 * value.h
 *
 *  Created on: 14 août 2018
 *      Author: ngrislain16
 */

#ifndef MARKET_V0_VALUE_H_
#define MARKET_V0_VALUE_H_

#include <iostream>
#include <string>
#include <boost/multi_array.hpp>

#include "../market_v0/demand.h"
#include "../market_v0/supply.h"

class StructuredNoisyValue {
private:
	typedef boost::multi_array<double, 2> DataType;
	typedef DataType::index IndexType;
	std::normal_distribution<double> distrib_;
	DataType structure_;
	DataType noise_;
public:
	StructuredNoisyValue(DataType structure, int supply_size, int demand_size, double mu, double sigma) :
		structure_(structure), noise_(boost::extents[supply_size][demand_size]), distrib_(mu, sigma) {}
	inline double operator()(unsigned long i, unsigned long j) {
		return structure_[i % structure_.shape()[0]][j % structure_.shape()[1]] +
						noise_[i % noise_.shape()[0]][j % noise_.shape()[1]];
	}
	inline double operator()(const Supply &s, const Demand &d) {
		return operator()(s.id(), d.id());
	}
	friend std::ostream& operator<<(std::ostream& os, const StructuredNoisyValue& v) {return os << "Value(supply size=" << v.noise_.shape()[0] << ", demand size=" << v.noise_.shape()[1] << ")";}

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

#endif /* MARKET_V0_VALUE_H_ */
