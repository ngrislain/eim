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
	for (Random *r : randoms_) {
		r->random();
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Omega& o) {
	return os << "Omega(" << o.randoms_.size() << " managed random variables)";
}
