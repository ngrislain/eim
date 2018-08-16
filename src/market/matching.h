/*
 * matching.h
 *
 *  Created on: 17 juil. 2018
 *      Author: ngrislain16
 */

#ifndef MATCHING_H_
#define MATCHING_H_

#include <iostream>
#include <string>
#include <boost/multi_array.hpp>
#include "supply.h"
#include "demand.h"

class BernoulliMatching {
private:
	typedef boost::multi_array<bool, 2> DataType;
	typedef DataType::index IndexType;
	std::bernoulli_distribution bernoulli_distrib_;
	DataType data_;
public:
	BernoulliMatching(double p, int supply_size, int demand_size) : bernoulli_distrib_(p), data_(boost::extents[supply_size][demand_size]) {}
//	Matching& full();
//	Matching& split(double share);
//	Matching& bernoulli(double p);
	// Required as a matching
	bool operator()(const Supply &s, const Demand &d);
	friend std::ostream& operator<<(std::ostream& os, const BernoulliMatching& matching);

	// Required for Omega::Ext
	template <typename G> void random(G g) {
		for (IndexType i=0; i<data_.shape()[0]; i++) {
			for (IndexType j=0; j<data_.shape()[1]; j++) {
				data_[i][j] = bernoulli_distrib_(g);
			}
		}
	}
};

#endif /* MATCHING_H_ */
