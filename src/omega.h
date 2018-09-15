/*
 * omega.h
 *
 *  Created on: 10 sept. 2018
 *      Author: ngrislain16
 */

#ifndef OMEGA_H_
#define OMEGA_H_

#include <set>
#include <random>
#include <iostream>

class Omega;
typedef std::mt19937_64 Generator;

// An interface for a Random Variable
class RandomVariable {
private:
	Omega &omega_;
public:
	RandomVariable(Omega &o);
	RandomVariable(const RandomVariable &rv) : RandomVariable(rv.omega_) {};
//	RandomVariable& operator=(const RandomVariable &rv) = default;
	virtual ~RandomVariable();
	// To be implemented
	virtual void draw(Generator &generator) = 0;
};

class Omega {
private:
	Generator seed_generator_;
	Generator value_generator_;
	std::set<RandomVariable*> random_variables_;
public:
	Omega() : seed_generator_(), value_generator_(seed_generator_()) {};
	Omega(unsigned long s) : seed_generator_(s), value_generator_(seed_generator_()) {};
	Omega& operator++();
	friend class RandomVariable;
	friend std::ostream& operator<<(std::ostream& os, const Omega& o);
};

#endif /* OMEGA_H_ */
