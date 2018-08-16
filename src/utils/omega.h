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
#include <iostream>

class Omega {
public:
	class Random;
	template <typename R> class Var;
	template <typename R, typename I> class Iter;
	template <typename E> class Ext;
private:
	std::mt19937_64 seed_generator_;
	std::mt19937_64 value_generator_;
	std::vector<Random> random_variables_;
public:
	Omega();
	Omega(unsigned long s);
	template <typename R> Var<R> operator()(R r) {return Var<R>(*this, r);}
	template <typename R, typename I> Iter<R,I> operator()(R r, I i) {return Iter<R,I>(*this, r, i);}
	template <typename E> Ext<E> ext(E &e) {return Ext<E>(*this, e);}
	Omega& operator++();
	friend std::ostream& operator<<(std::ostream& os, const Omega& o);

	// Generic Random value definition
	class Random {
	private:
		virtual void random(Omega &o) = 0;
	public:
		virtual ~Random() = default;
		friend Omega& Omega::operator++();
	};

	// Var definition
	template <typename R>
	class Var : Random {
	private:
		typedef typename R::result_type T;
		R random_;
		T value_;
		virtual void random(Omega &o) {value_ = random_(o.value_generator_);}
	public:
		Var(Omega &o, R r) : random_(r) {
			o.random_variables_.push_back(this);
			random(o);
		}
		virtual ~Var() = default;
		inline T operator()() const {return value_;}
		friend std::ostream& operator<<(std::ostream& os, const Var& v) {return os << v.value_;}
	};

	// Iter definition
	template <typename R, typename I>
	class Iter : Random {
	private:
		typedef typename R::result_type T;
		R random_;
		I iter_;
		virtual void random(Omega &o) {
			auto val = iter_.begin();
			auto end = iter_.end();
			while(val != end) {
				*val = random_(o.value_generator_);
				++val;
			}
		}
	public:
		Iter(Omega &o, R r, I i) : random_(r), iter_(i) {
			o.random_variables_.push_back(this);
			random(o);
		}
		virtual ~Iter() = default;
		inline I operator()() const {return iter_;}
		friend std::ostream& operator<<(std::ostream& os, const Iter& i) {
			auto val = i.iter_.begin();
			auto end = i.iter_.end();
			os << "[" << *val;
			++val;
			while(val != end) {
				os << ", " << *val;
				++val;
			}
			os << "]";
			return os;
		}
	};
	// Ext definition
	template <typename E>
	class Ext : Random {
	private:
		E &ext_;
		virtual void random(Omega &o) {
			std::cout << "DEBUG Ext::random" << std::endl;
			ext_.random(o.value_generator_);
			std::cout << "DEBUG Ext::random" << std::endl;
		}
	public:
		Ext(Omega &o, E &e) : ext_(e) {
			o.random_variables_.push_back(this);
			random(o);
		}
		virtual ~Ext() = default;
	};
	Var<std::uniform_int_distribution<unsigned long>> integer() {return operator()(std::uniform_int_distribution<unsigned long>());}
	Var<std::uniform_real_distribution<double>> real() {return operator()(std::uniform_real_distribution<double>());}
	Var<std::normal_distribution<double>> norm() {return operator()(std::normal_distribution<double>());}
	template <typename I> Iter<std::uniform_int_distribution<unsigned long>,I> integer(I i) {return operator()(std::uniform_int_distribution<unsigned long>(), i);}
	template <typename I> Iter<std::uniform_real_distribution<double>,I> real(I i) {return operator()(std::uniform_real_distribution<double>(), i);}
	template <typename I> Iter<std::normal_distribution<double>,I> norm(I i) {return operator()(std::normal_distribution<double>(), i);}
};

#endif /* UTILS_OMEGA_H_ */
