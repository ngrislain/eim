/*
 * Entity.cpp
 *
 *  Created on: 7 août 2018
 *      Author: ngrislain16
 */

#include <functional>
#include <random>
#include "entity.h"

using namespace std;

DeterministicGenerator::DeterministicGenerator(const DeterministicGenerator& dg) : seed(dg.seed) {}
DeterministicGenerator::DeterministicGenerator(unsigned long s) : seed(s) {}

unsigned long DeterministicGenerator::operator()() {
	return seed;
}

// Initialize static members
mt19937_64 Entity::gen;
uniform_int_distribution<unsigned long> Entity::distrib;

Entity::Entity() : id(distrib(Entity::gen)) {}

DeterministicGenerator Entity::generator(int index) {
	return DeterministicGenerator(hash<unsigned long>{}(id+index));
}

DeterministicGenerator Entity::generator(string index) {
	return DeterministicGenerator(hash<unsigned long>{}(id+hash<string>{}(index)));
}
