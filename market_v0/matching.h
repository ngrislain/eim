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

#include "../market_v0/demand.h"
#include "../market_v0/supply.h"

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
	double supply_share_;
	double demand_share_;
public:
	SplitMatching(double supply_share, double demand_share) : supply_share_(supply_share), demand_share_(demand_share) {}
	// Required as a matching
	inline bool operator()(unsigned long i, unsigned long j) {
		return ((i % p_) < supply_share_*p_ && (j % p_) < demand_share_*p_) ||
			((i % p_) >= supply_share_*p_ && (j % p_) >= demand_share_*p_) ?
			1 : 0;
	}
	inline bool operator()(const Supply &s, const Demand &d) {
		return operator()(s.id(), d.id());
	}
	friend std::ostream& operator<<(std::ostream& os, const SplitMatching& m) {return os << "SplitMatching(supply share=" << m.supply_share_ << ", demand share=" << m.demand_share_ << ")";}

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
	inline double marginal(const Supply &s) {
		double result = 0;
		for (int j=0; j<data_.shape()[1]; j++) {
			result += data_[s.id() % data_.shape()[0]][j];
		}
		return result/data_.shape()[1];
	}
	inline double marginal(const Demand &d) {
		double result = 0;
		for (int i=0; i<data_.shape()[0]; i++) {
			result += data_[i][d.id() % data_.shape()[1]];
		}
		return result/data_.shape()[0];
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
