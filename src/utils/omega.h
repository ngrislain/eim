/*
 * omega.h
 *
 *  Created on: 14 août 2018
 *      Author: ngrislain16
 */

#ifndef UTILS_OMEGA_H_
#define UTILS_OMEGA_H_

#include <array>
#include <vector>
#include <random>
#include <functional>

class Omega {
public:
	class Random;
	template <typename R> class Var;
	template <typename R, typename I> class Iter;
private:
	static std::uniform_int_distribution<unsigned long> uniform_long;
	static std::uniform_real_distribution<double> uniform_double;
	static std::normal_distribution<double> normal;
	std::mt19937_64 seed_generator_;
	std::mt19937_64 value_generator_;
	std::vector<Random*> values_;
public:
	Omega();
	Omega(unsigned long s);
	template <typename R> Var<R> operator()(R &r) {return Var<R>(*this, r);}
	template <typename R, typename I> Iter<R,I> operator()(R &r, I &i) {return Iter<R,I>(*this, r, i);}
	template <typename R, typename I> Iter<R,I> operator()(R &r, I &&i) {return Iter<R,I>(*this, r, i);}
	Omega& operator++();
	friend std::ostream& operator<<(std::ostream& os, const Omega& o);
	// Generic Random value definition
	class Random {
	private:
		virtual void random(Omega &o) = 0;
		friend Omega& Omega::operator++();
	public:
		virtual ~Random() = default;
	};
	// Var definition
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
	// Iter class
	template <typename R, typename I>
	class Iter : Random {
	private:
		typedef typename R::result_type T;
		R &random_;
		I &iter_;
		Iter(Omega &o, R &r, I &i) : random_(r), iter_(i) {
			o.values_.push_back(this);
			random(o);
		}
		Iter(Omega &o, R &r, I &&i) : random_(r), iter_(std::move(i)) {
			o.values_.push_back(this);
			random(o);
		}
		virtual void random(Omega &o) {
			auto val = iter_.begin();
			auto end = iter_.end();
			while(val != end) {
				*val = random_(o.value_generator_);
				++val;
			}
		}
	public:
	virtual ~Iter() = default;
	inline I operator()() const {return iter_;}
	friend class Omega;
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
	Var<std::uniform_int_distribution<unsigned long>> integer() {return operator()(uniform_long);}
	Var<std::uniform_real_distribution<double>> real() {return operator()(uniform_double);}
	Var<std::normal_distribution<double>> norm() {return operator()(normal);}
	template <typename I> Iter<std::uniform_int_distribution<unsigned long>,I> integer(I &&i) {return operator()(uniform_long, i);}
	template <typename I> Iter<std::uniform_real_distribution<double>,I> real(I &&i) {return operator()(uniform_double, i);}
	template <typename I> Iter<std::normal_distribution<double>,I> norm(I &&i) {return operator()(normal, i);}
};

#endif /* UTILS_OMEGA_H_ */
