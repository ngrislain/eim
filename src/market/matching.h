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

class Matching {
private:
	typedef boost::multi_array<bool, 2> DataType;
	typedef DataType::index IndexType;
	DataType data_;
	std::mt19937_64 gen;
public:
	unsigned long id;
	Matching(int supply_size, int demand_size);
	Matching& full();
	Matching& split(double share);
	Matching& bernoulli(double p);
	DataType data() const;
	bool operator()(const Supply &s, const Demand &d) const;
	friend std::ostream& operator<<(std::ostream& os, const Matching& matching);
};

#endif /* MATCHING_H_ */
