/*
 * omega.h
 *
 *  Created on: 14 août 2018
 *      Author: ngrislain16
 */

#ifndef UTILS_OMEGA_H_
#define UTILS_OMEGA_H_

#include <vector>
#include <random>
#include <functional>

typedef std::mt19937_64 Generator;
class Random;
template <typename R>
class Var;

class Omega {
private:
	Generator seed_generator_;
	Generator value_generator_;
	std::vector<Random*> values_;
public:
	Omega();
	Omega(unsigned long s);
	template <typename R> Var<R> operator()(R &r) {return Var<R>(*this, r);}
	Omega& operator++();
	friend class Random;
	template <typename R> friend class Var;
	friend std::ostream& operator<<(std::ostream& os, const Omega& o);
};

// Generic Random value definition
class Random {
private:
	virtual void random(Omega &o) = 0;
	friend Omega& Omega::operator++();
public:
	virtual ~Random() = default;
};

// Value definition
template <typename R>
class Var : Random {
private:
	typedef typename R::result_type T;
	T value_;
	R &random_;
	Var(Omega &o, R &r) : random_(r) {
		o.values_.push_back(this);
		random(o);
	}
	virtual void random(Omega &o) {value_ = random_(o.value_generator_);}
public:
	virtual ~Var() = default;
	inline T operator()() const {return value_;}
	friend class Omega;
	friend std::ostream& operator<<(std::ostream& os, const Var& v) {return os << v.value_;}
};

#endif /* UTILS_OMEGA_H_ */
