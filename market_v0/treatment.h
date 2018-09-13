/*
 * treatment.h
 *
 *  Created on: 20 août 2018
 *      Author: ngrislain16
 */

#ifndef MARKET_V0_TREATMENT_H_
#define MARKET_V0_TREATMENT_H_

#include <iostream>
#include <cstdlib>
#include <boost/multi_array.hpp>

#include "../market_v0/demand.h"
#include "../market_v0/supply.h"

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
	typedef boost::multi_array<double, 2> DataType;
	typedef DataType::index IndexType;
	double treatment_;
	std::bernoulli_distribution bernoulli_distrib_;
	DataType data_;
public:
	BernoulliTreatment(double treatment, double p, int supply_size, int demand_size) : treatment_(treatment), bernoulli_distrib_(p), data_(boost::extents[supply_size][demand_size]) {}
	// Required as a matching
	inline double operator()(unsigned long i, unsigned long j) {
		return data_[i % data_.shape()[0]][j % data_.shape()[1]];
	}
	inline double operator()(const Supply &s, const Demand &d) {
		return operator()(s.id(), d.id());
	}
	inline double marginal(const Supply &s) {
		double result = 0;
		for (int j=0; j<data_.shape()[1]; j++) {
			result += (data_[s.id() % data_.shape()[0]][j] != 1);
		}
		return result/data_.shape()[1];
	}
	inline double marginal(const Demand &d) {
		double result = 0;
		for (int i=0; i<data_.shape()[0]; i++) {
			result += (data_[i][d.id() % data_.shape()[1]] != 1);
		}
		return result/data_.shape()[0];
	}
	friend std::ostream& operator<<(std::ostream& os, const BernoulliTreatment& t);

	// Required for Omega::Ext
	template <typename G> void random(G &g) {
		for (IndexType i=0; i<data_.shape()[0]; i++) {
			for (IndexType j=0; j<data_.shape()[1]; j++) {
				data_[i][j] = bernoulli_distrib_(g) ? std::exp(treatment_) : 1;
			}
		}
	}
};

class CompoundBernoulliTreatment {
private:
	typedef boost::multi_array<double, 2> DataType;
	typedef DataType::index IndexType;
	double treatment_;
	std::gamma_distribution<double> a_distrib_;
	std::gamma_distribution<double> b_distrib_;// a beta distrib is the ratio of a/(a+b)
	std::uniform_real_distribution<double> uniform_distrib_;
	DataType data_;
public:
	CompoundBernoulliTreatment(double treatment, double a, double b, int supply_size, int demand_size) : treatment_(treatment), a_distrib_(a), b_distrib_(b), data_(boost::extents[supply_size][demand_size]) {}
	// Required as a matching
	inline double operator()(unsigned long i, unsigned long j) {
		return data_[i % data_.shape()[0]][j % data_.shape()[1]];
	}
	inline double operator()(const Supply &s, const Demand &d) {
		return operator()(s.id(), d.id());
	}
	inline double marginal(const Supply &s) {
		double result = 0;
		for (int j=0; j<data_.shape()[1]; j++) {
			result += (data_[s.id() % data_.shape()[0]][j] != 1);
		}
		return result/data_.shape()[1];
	}
	inline double marginal(const Demand &d) {
		double result = 0;
		for (int i=0; i<data_.shape()[0]; i++) {
			result += (data_[i][d.id() % data_.shape()[1]] != 1);
		}
		return result/data_.shape()[0];
	}
	friend std::ostream& operator<<(std::ostream& os, const CompoundBernoulliTreatment& t);

	// Required for Omega::Ext
	template <typename G> void random(G &g) {
		double x;
		double y;
		double threshold;
		for (IndexType j=0; j<data_.shape()[1]; j++) {// Threshold set per demand
			x = a_distrib_(g);
			y = b_distrib_(g);
			threshold = x/(x+y);
			for (IndexType i=0; i<data_.shape()[0]; i++) {
				data_[i][j] = (uniform_distrib_(g)<threshold) ? std::exp(treatment_) : 1;
			}
		}
	}
};

#endif /* MARKET_V0_TREATMENT_H_ */
