/*
 * market.h
 *
 *  Created on: 13 sept. 2018
 *      Author: ngrislain16
 */

#ifndef MARKET_H_
#define MARKET_H_

#include <array>
#include <vector>
#include "omega.h"
#include "json.h"

namespace market {
static constexpr int supply_dim = 100;
static constexpr int demand_dim = 100;
static constexpr int feature_dim = 5;
static constexpr int supply_split_dim = 100;
static constexpr int demand_split_dim = 100;
static constexpr int market_iterations = 10;

// Some interpretations of the main feature factors
enum Feature : int {
	constant_feature = 0, days_before_departure_feature = 1, price_feature = 2, geo_feature = 3
};

class Agent : RandomVariable, public json::Serializable {
private:
	unsigned long id_;
	std::array<double,feature_dim> features_;
public:
	Agent(Omega &o) : RandomVariable(o), id_(0) {};
	unsigned long id() const {return id_;};
	double feature(int i) const {return features_[i];};
	virtual void draw(Generator &generator) override;
	virtual std::ostream& json(std::ostream& os, int indent = 0) const override;
};

class Supply : public Agent {
public:
	Supply(Omega &o) : Agent(o) {};
	double days_before_departure() const;
	virtual std::ostream& json(std::ostream& os, int indent = 0) const override;
};

class Demand : public Agent {
public:
	Demand(Omega &o) : Agent(o) {};
	double days_before_departure() const;
	virtual std::ostream& json(std::ostream& os, int indent = 0) const override;
};

class Value : RandomVariable, public json::Serializable {
protected:
	std::array<double,feature_dim*feature_dim> parameters_;
public:
	Value(Omega &o) : RandomVariable(o) {};
	std::array<double,feature_dim*feature_dim> parameters() const {return parameters_;}
	double operator()(const Supply &s, const Demand &d) const;
	virtual void draw(Generator &generator) override = 0;
	virtual std::ostream& json(std::ostream& os, int indent = 0) const override;
};

class NormalValue : public Value {
public:
	NormalValue(Omega &o) : Value(o) {};
	virtual void draw(Generator &generator) override;
};

class SoftValue : public Value {
public:
	SoftValue(Omega &o) : Value(o) {};
	virtual void draw(Generator &generator) override;
};

class Modifier : RandomVariable, public json::Serializable {
protected:
	std::array<double,supply_split_dim*demand_split_dim> parameters_;
public:
	Modifier(Omega &o) : RandomVariable(o) {};
	std::array<double,supply_split_dim*demand_split_dim> parameters() const {return parameters_;}
	double operator()(const Supply &s, const Demand &d, const Value &v, double impact) const;
	virtual void draw(Generator &generator) override = 0;
	virtual std::ostream& json(std::ostream& os, int indent = 0) const override;
};

class TreatmentModifier : public Modifier {
private:
	double proba_;
public:
	TreatmentModifier(Omega &o, double proba=0.5) : Modifier(o), proba_(proba) {};
	TreatmentModifier& proba(double p);
	virtual void draw(Generator &generator) override;
};

class SupplyTreatmentModifier : public Modifier {
private:
	double proba_;
public:
	SupplyTreatmentModifier(Omega &o, double proba=0.5) : Modifier(o), proba_(proba) {};
	SupplyTreatmentModifier& proba(double p);
	virtual void draw(Generator &generator) override;
};

class MatchingModifier : public Modifier {
private:
	double proba_;
public:
	MatchingModifier(Omega &o, double proba=0.9) : Modifier(o), proba_(proba) {};
	double operator()(const Supply &s, const Demand &d, const Value &v) const;
	MatchingModifier& proba(double p);
	virtual void draw(Generator &generator) override;
};

struct Result : public json::Serializable {
	int sample_size;
	double treated_share;
	double gmv_mean, gmv_min, gmv_low, gmv_med, gmv_high, gmv_max;
	virtual std::ostream& json(std::ostream& os, int indent = 0) const override;
};

struct SupplyValue : public json::Serializable {
	Supply *supply;
	double value;
	SupplyValue(Supply *supply, double value) : supply(supply), value(value) {}
	virtual std::ostream& json(std::ostream& os, int indent = 0) const override;
};

struct DemandValue : public json::Serializable {
	Demand *demand;
	double value;
	DemandValue(Demand *demand, double value) : demand(demand), value(value) {}
	virtual std::ostream& json(std::ostream& os, int indent = 0) const override;
};

class Experiment {
public:
	// General fields
	Omega omega;
	Omega long_term_omega;
	std::vector<Supply> supply;
	std::vector<Demand> demand;
	// Create maps for book-keeping;
	std::set<Supply*> supply_searching;
	std::set<Demand*> demand_searching;
	std::multimap<Supply*, DemandValue> supply_candidates;
	std::multimap<Demand*, SupplyValue> demand_candidates;
	std::map<Supply*, Demand*> matched;
	bool match = false;
	// Values and modifiers
	SoftValue supply_value;
	NormalValue demand_value;
	TreatmentModifier treatment;
	double supply_impact = 0;
	double demand_impact = 0.2;
	Experiment();
	Result run(int sample_size, double treated_share);
	void reset();
	void demand_propose();
	double supply_dispose();
	void print();
};

}
#endif /* MARKET_H_ */
