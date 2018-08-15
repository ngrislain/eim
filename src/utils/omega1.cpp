/*
 * omega.cpp
 *
 *  Created on: 13 août 2018
 *      Author: ngrislain16
 */

#include "omega.h"

#include <iostream>

using namespace std;

std::mt19937_64 Omega::generator{std::random_device{}()};
Omega Omega::instance{};

Omega::Omega() : state_(Omega::generator()), generator_(state_) {}

Omega::Generator<Omega> Omega::operator[](const unsigned long s) {
	return Omega::Generator<Omega>(*this, s);
}

Omega::Generator<Omega> Omega::operator[](const std::string s) {
	return Omega::Generator<Omega>(*this, s);
}

unsigned long Omega::operator()() const {
	return state_;
}

Omega& Omega::operator++() {
	state_ = generator_();
	return *this;
}
