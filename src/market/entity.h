/*
 * Entity.h
 *
 *  Created on: 7 août 2018
 *      Author: ngrislain16
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>
#include <random>

#include "../utils/d_gen.h"

class Entity {
private:
	static std::mt19937_64 gen;
	static std::uniform_int_distribution<unsigned long> distrib;
	unsigned long id_;
public:
	Entity();
	Entity& init();
	unsigned long id() const;
	DeterministicGenerator d_gen(int index) const;
	DeterministicGenerator d_gen(std::string index) const;
};

#endif /* ENTITY_H_ */
