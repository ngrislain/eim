/*
 * omega.cpp
 *
 *  Created on: 14 août 2018
 *      Author: ngrislain16
 */

#include "omega.h"

Omega::Omega() : seed_generator_(), value_generator_(seed_generator_()) {}

Omega::Omega(unsigned long s) : seed_generator_(s), value_generator_(seed_generator_()) {}

Omega& Omega::operator++() {
	value_generator_.seed(seed_generator_());
	for (Random *value : values_) {
		value->random(*this);
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Omega& o) {
	return os << "Omega(" << o.values_.size() << " managed random variables)";
}
