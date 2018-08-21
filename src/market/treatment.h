/*
 * treatment.h
 *
 *  Created on: 20 août 2018
 *      Author: ngrislain16
 */

#ifndef MARKET_TREATMENT_H_
#define MARKET_TREATMENT_H_

#include <cstdlib>
#include "supply.h"
#include "demand.h"

class FullTreatment {
private:
	double treatment_;
public:
	FullTreatment(double treatment) : treatment_(treatment) {}
	// Required as a treatment
	inline bool operator()(unsigned long i, unsigned long j) {return std::exp(treatment_);}
	inline bool operator()(const Supply &s, const Demand &d) {
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
	double share_;
public:
	SplitTreatment(double treatment, double share) : treatment_(treatment), share_(share) {}
	// Required as a matching
	inline bool operator()(unsigned long i, unsigned long j) {
		return ((i%p_) < share_*p_ && (j%p_) < share_*p_) ||
			((i%p_) >= share_*p_ && (j%p_) >= share_*p_) ?
					std::exp(treatment_) : 1;
	}
	inline bool operator()(const Supply &s, const Demand &d) {
		return operator()(s.id(), d.id());
	}
	friend std::ostream& operator<<(std::ostream& os, const SplitTreatment& t) {return os << "SplitTreatment(" << t.treatment_ << ", " << t.share_ << ")";}

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
	inline bool operator()(unsigned long i, unsigned long j) {
		return data_[i % data_.shape()[0]][j % data_.shape()[1]];
	}
	inline bool operator()(const Supply &s, const Demand &d) {
		return operator()(s.id(), d.id());
	}
	friend std::ostream& operator<<(std::ostream& os, const BernoulliTreatment& m);

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
