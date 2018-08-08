/*
 * Entity.h
 *
 *  Created on: 7 août 2018
 *      Author: ngrislain16
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include <random>

class Entity {
private:
	static std::mt19937_64 gen;
	static std::uniform_int_distribution<unsigned long> distrib;
public:
	Entity();
	unsigned long id;
	double rand(int index=0);
};

#endif /* ENTITY_H_ */
