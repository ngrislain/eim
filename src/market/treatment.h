/*
 * treatment.h
 *
 *  Created on: 20 août 2018
 *      Author: ngrislain16
 */

#ifndef MARKET_TREATMENT_H_
#define MARKET_TREATMENT_H_

#include <iostream>
#include <cstdlib>
#include <boost/multi_array.hpp>
#include "supply.h"
#include "demand.h"

class FullTreatment {
private:
	double treatment_;
public:
	FullTreatment(double treatment) : treatment_(treatment) {}
	// Required as a treatment
	inline double operator()(unsigned long i, unsigned long j) {return std::exp(treatment_);}
	inline double operator()(const Supply &s, const Demand &d) {
		return operator()(s.id(), d.id());
	}
	friend std::ostream& operator<<(std::ostream& os, const FullTreatment& t) {return os << "FullTreatment(" << t.treatment_ << ")";}

	// Required for Omega::Ext
	template <typename G> void random(G &g) {}
};

class SplitTreatment {
private:
	static constexpr int p_ = 9341837;
	double treatment_;
	double supply_share_;
	double demand_share_;
public:
	SplitTreatment(double treatment, double supply_share, double demand_share) : treatment_(treatment), supply_share_(supply_share), demand_share_(demand_share) {}
	// Required as a matching
	inline double operator()(unsigned long i, unsigned long j) {
		return ((i%p_) < supply_share_*p_ && (j%p_) < demand_share_*p_) ||
			((i%p_) >= supply_share_*p_ && (j%p_) >= demand_share_*p_) ?
					std::exp(treatment_) : 1;
	}
	inline double operator()(const Supply &s, const Demand &d) {
		return operator()(s.id(), d.id());
	}
	friend std::ostream& operator<<(std::ostream& os, const SplitTreatment& t) {return os << "SplitTreatment(treatment=" << t.treatment_ << ", supply share=" << t.supply_share_ << ", demand share=" << t.demand_share_ << ")";}

	// Required for Omega::Ext
	template <typename G> void random(G &g) {}
};

class BernoulliTreatment {
private:
	typedef boost::multi_array<bool, 2> DataType;
	typedef DataType::index IndexType;
	std::bernoulli_distribution bernoulli_distrib_;
	DataType data_;
public:
	BernoulliTreatment(double p, int supply_size, int demand_size) : bernoulli_distrib_(p), data_(boost::extents[supply_size][demand_size]) {}
	// Required as a matching
	inline double operator()(unsigned long i, unsigned long j) {
		return data_[i % data_.shape()[0]][j % data_.shape()[1]];
	}
	inline double operator()(const Supply &s, const Demand &d) {
		return operator()(s.id(), d.id());
	}
	friend std::ostream& operator<<(std::ostream& os, const BernoulliTreatment& t);

	// Required for Omega::Ext
	template <typename G> void random(G &g) {
		for (IndexType i=0; i<data_.shape()[0]; i++) {
			for (IndexType j=0; j<data_.shape()[1]; j++) {
				data_[i][j] = bernoulli_distrib_(g);
			}
		}
	}
};

#endif /* MARKET_TREATMENT_H_ */
