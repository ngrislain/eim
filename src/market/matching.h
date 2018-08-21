/*
 * matching.h
 *
 *  Created on: 17 juil. 2018
 *      Author: ngrislain16
 */

#ifndef MATCHING_H_
#define MATCHING_H_

#include <iostream>
#include <boost/multi_array.hpp>
#include "supply.h"
#include "demand.h"

class FullMatching {
public:
	FullMatching() {}
	// Required as a matching
	inline bool operator()(unsigned long i, unsigned long j) {return 1;}
	inline bool operator()(const Supply &s, const Demand &d) {
		return operator()(s.id(), d.id());
	}
	friend std::ostream& operator<<(std::ostream& os, const FullMatching& m) {return os << "FullMatching()";}

	// Required for Omega::Ext
	template <typename G> void random(G &g) {}
};

class SplitMatching {
private:
	static constexpr int p_ = 9634721;
	double share_;
public:
	SplitMatching(double share) : share_(share) {}
	// Required as a matching
	inline bool operator()(unsigned long i, unsigned long j) {
		return ((i % p_) < share_*p_ && (j % p_) < share_*p_) ||
			((i % p_) >= share_*p_ && (j % p_) >= share_*p_) ?
			1 : 0;
	}
	inline bool operator()(const Supply &s, const Demand &d) {
		return operator()(s.id(), d.id());
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
	inline bool operator()(unsigned long i, unsigned long j) {
		return data_[i % data_.shape()[0]][j % data_.shape()[1]];
	}
	inline bool operator()(const Supply &s, const Demand &d) {
		return operator()(s.id(), d.id());
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
