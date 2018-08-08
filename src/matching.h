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
#include "boost/multi_array.hpp"
#include "boost/random.hpp"

class Matching {
private:
	int supply_size;
	int demand_size;
	//boost::multi_array<bool, 2> matrix;
	boost::mt19937 random_number_generator;
public:
	boost::multi_array<bool, 2> matrix;

	Matching(int supply_size, int demand_size);
	Matching& full_matching();
	Matching& split_matching(float share);
	Matching& bernoulli_matching(float p);
	friend std::ostream& operator<<(std::ostream& os, const Matching& matching);
};



#endif /* MATCHING_H_ */
