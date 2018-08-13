/*
 * deterministic_generator.cpp
 *
 *  Created on: 13 août 2018
 *      Author: ngrislain16
 */

#include "d_gen.h"

using namespace std;

// Define deterministic generators

DeterministicGenerator::DeterministicGenerator(const DeterministicGenerator& dg) : seed_(dg.seed_) {}

DeterministicGenerator::DeterministicGenerator(const unsigned long s) : seed_(s) {}

unsigned long DeterministicGenerator::operator()() {
	return seed_;
}

