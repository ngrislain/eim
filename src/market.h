/*
 * market.h
 *
 *  Created on: 13 sept. 2018
 *      Author: ngrislain16
 */

#ifndef MARKET_H_
#define MARKET_H_

#include <array>
#include "omega.h"

static constexpr int supply_dim = 1000;
static constexpr int demand_dim = 1000;
static constexpr int feature_dim = 7;

// Some interpretations of the main feature factors
enum Feature : int {
	constant_feature = 0, days_before_departure_feature = 1, price_feature = 2, geo_feature = 3
};

class Agent : RandomVariable {
private:
	unsigned long id_;
	std::array<double,feature_dim> features_;
public:
	Agent(Omega &o) : RandomVariable(o), id_(0) {};
	unsigned long id() const {return id_;};
	double feature(int i) const {return features_[i];};
	virtual void draw(Generator &generator) override;
};

class Driver : Agent {
public:
	Driver(Omega &o) : Agent(o) {};
	double days_before_departure() const;
	friend std::ostream& operator<<(std::ostream& os, const Driver& d);
};

class Passenger : Agent {
public:
	Passenger(Omega &o) : Agent(o) {};
	double days_before_departure() const;
	friend std::ostream& operator<<(std::ostream& os, const Passenger& p);
};

#endif /* MARKET_H_ */
