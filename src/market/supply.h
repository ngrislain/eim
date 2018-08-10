/*
 * Supply.h
 *
 *  Created on: 7 août 2018
 *      Author: ngrislain16
 */

#ifndef SUPPLY_H_
#define SUPPLY_H_

#include "entity.h"

#include <chrono>

class Supply : public Entity {
public:
	std::chrono::system_clock::time_point travel_date;
	std::chrono::system_clock::time_point enter_date;
	Supply();
};

#endif /* SUPPLY_H_ */
