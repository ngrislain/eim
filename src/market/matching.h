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
#include <limits>
#include <boost/multi_array.hpp>
#include "supply.h"
#include "demand.h"

class FullMatching {
public:
	FullMatching() {}
	// Required as a matching
	inline bool operator()(const Supply &s, const Demand &d) {return 1;}
	friend std::ostream& operator<<(std::ostream& os, const FullMatching& m) {return os << "FullMatching()";}

	// Required for Omega::Ext
	template <typename G> void random(G &g) {}
};

class SplitMatching {
private:
	double share_;
public:
	SplitMatching(double share) : share_(share) {}
	// Required as a matching
	inline bool operator()(const Supply &s, const Demand &d) {
		return (s.id() < share_*std::numeric_limits<unsigned long>::max() && d.id() < share_*std::numeric_limits<unsigned long>::max()) ||
			(s.id() >= share_*std::numeric_limits<unsigned long>::max() && d.id() >= share_*std::numeric_limits<unsigned long>::max()) ?
			1 : 0;
	}
	friend std::ostream& operator<<(std::ostream& os, const SplitMatching& m) {return os << "SplitMatching(" << m.share_ << ")";}

	// Required for Omega::Ext
	template <typename G> void random(G &g) {}
};

class BernoulliMatching {
private:
	typedef boost::multi_array<bool, 2> DataType;
	typedef DataType::index IndexType;
	std::bernoulli_distribution bernoulli_distrib_;
	DataType data_;
public:
	BernoulliMatching(double p, int supply_size, int demand_size) : bernoulli_distrib_(p), data_(boost::extents[supply_size][demand_size]) {}
	// Required as a matching
	inline bool operator()(const Supply &s, const Demand &d) {
		return data_[s.id() % data_.shape()[0]][d.id() % data_.shape()[1]];
	}
	friend std::ostream& operator<<(std::ostream& os, const BernoulliMatching& m);

	// Required for Omega::Ext
	template <typename G> void random(G &g) {
		for (IndexType i=0; i<data_.shape()[0]; i++) {
			for (IndexType j=0; j<data_.shape()[1]; j++) {
				data_[i][j] = bernoulli_distrib_(g);
			}
		}
	}
};

#endif /* MATCHING_H_ */
