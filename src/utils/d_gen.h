/*
 * deterministic_generator.h
 *
 *  Created on: 13 août 2018
 *      Author: ngrislain16
 */

#ifndef UTILS_D_GEN_H_
#define UTILS_D_GEN_H_

#include <limits>

class DeterministicGenerator {
private:
	unsigned long seed_;
public:
	typedef unsigned long result_type;
	static constexpr unsigned long min() {return std::numeric_limits<unsigned long>::min();};
	static constexpr unsigned long max() {return std::numeric_limits<unsigned long>::max();};
	DeterministicGenerator(const DeterministicGenerator& dg);
	DeterministicGenerator(const unsigned long s);
	unsigned long operator()();
};

#endif /* UTILS_D_GEN_H_ */
