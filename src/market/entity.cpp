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

// Define Entity

// Initialize static members
mt19937_64 Entity::gen;
uniform_int_distribution<unsigned long> Entity::distrib;

Entity::Entity() : id_(distrib(gen)) {}

Entity& Entity::init() {
	id_ = distrib(gen);
	return *this;
}

unsigned long Entity::id() const {
	return id_;
}

DeterministicGenerator Entity::d_gen(int index) const {
	gen.seed(id()+index);
	return DeterministicGenerator(gen());
}

DeterministicGenerator Entity::d_gen(string index) const {
	gen.seed(id()+hash<string>{}(index));
	return DeterministicGenerator(gen());
}
