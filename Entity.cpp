/*
 * Entity.cpp
 *
 *  Created on: 7 août 2018
 *      Author: ngrislain16
 */

#include "Entity.h"
#include <limits>
#include <functional>
#include <random>

using namespace std;

// Initialize static members
mt19937_64 Entity::gen;
uniform_int_distribution<unsigned long> Entity::distrib;

Entity::Entity() {
	id = distrib(Entity::gen);
}

double Entity::rand(int index) {
	return hash<unsigned long>{}(id+index)/(double)numeric_limits<unsigned long>::max();
}
