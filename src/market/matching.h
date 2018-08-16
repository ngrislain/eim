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
#include "../utils/omega.h"

class BernoulliMatching {
private:
	typedef boost::multi_array<bool, 2> DataType;
	typedef DataType::index IndexType;
	DataType data_;
public:
	BernoulliMatching(Omega & o, double p, int supply_size, int demand_size);
	//Omega::Iter<std::bernoulli_distribution, DataType::> data;

//	Matching& full();
//	Matching& split(double share);
//	Matching& bernoulli(double p);
	bool operator()(const Supply &s, const Demand &d);// required as a matching
	friend std::ostream& operator<<(std::ostream& os, const BernoulliMatching& matching);
};

#endif /* MATCHING_H_ */
