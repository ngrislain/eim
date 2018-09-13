/*
 * omega.cpp
 *
 *  Created on: 10 sept. 2018
 *      Author: ngrislain16
 */

#include "omega.h"

// RandomVariable implementation

RandomVariable::RandomVariable(Omega &o) : omega_(o) {
	// We add an entry to omega
	omega_.random_variables_.insert(this);
};

RandomVariable::~RandomVariable() {
	// We remove the entry
	omega_.random_variables_.erase(this);
};

// Omega implementation

Omega& Omega::operator++() {
	value_generator_.seed(seed_generator_());
	for (RandomVariable *rv : random_variables_) {
		rv->draw(value_generator_);
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Omega& o) {
	return os << "{" << std::endl <<
			"  \"type\":\"Omega\"," << std::endl <<
			"  \"size\":" << o.random_variables_.size() << std::endl <<
			"}";
}

