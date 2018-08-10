/*
 * Entity.h
 *
 *  Created on: 7 août 2018
 *      Author: ngrislain16
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <limits>
#include <string>
#include <random>

class DeterministicGenerator {
private:
	const unsigned long seed;
public:
	typedef unsigned long result_type;
	static constexpr unsigned long min() {return std::numeric_limits<unsigned long>::min();};
	static constexpr unsigned long max() {return std::numeric_limits<unsigned long>::max();};
	DeterministicGenerator(const DeterministicGenerator& dg);
	DeterministicGenerator(unsigned long s);
	unsigned long operator()();
};

class Entity {
private:
	static std::mt19937_64 gen;
	static std::uniform_int_distribution<unsigned long> distrib;
public:
	Entity();
	const unsigned long id;
	DeterministicGenerator generator(int index);
	DeterministicGenerator generator(std::string index);
};

#endif /* ENTITY_H_ */
