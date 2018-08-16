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
	template <typename R, int n> class VarArray;
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
	template <typename R, int n> VarArray<R,n> array(R &r) {return VarArray<R,n>(*this, r);}
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
	template <typename R, int n>
	class VarArray : Random {
	private:
		typedef typename R::result_type T;
		std::array<T,n> values_;
		R &random_;
		VarArray(Omega &o, R &r) : random_(r) {
			o.values_.push_back(this);
			random(o);
		}
		virtual void random(Omega &o) {
			for (int i=0; i<n; i++) {
				values_[i] = random_(o.value_generator_);
			}
		}
	public:
		virtual ~VarArray() = default;
		inline std::array<T,n> operator()() const {return values_;}
		friend class Omega;
		friend std::ostream& operator<<(std::ostream& os, const VarArray& va) {
			os << "[" << va.values_[0];
			for (int i=1; i<n; i++) {
				os << ", " << va.values_[i];
			}
			os << "]";
			return os;
		}
	};
	Var<std::uniform_int_distribution<unsigned long>> operator()() {return operator()(uniform_long);}
	Var<std::uniform_real_distribution<double>> unif() {return operator()(uniform_double);}
	Var<std::normal_distribution<double>> norm() {return operator()(normal);}
	template <int n> VarArray<std::uniform_int_distribution<unsigned long>,n> array() {return VarArray<std::uniform_int_distribution<unsigned long>,n>(*this, uniform_long);}
	template <int n> VarArray<std::uniform_real_distribution<double>,n> unif_array() {return VarArray<std::uniform_real_distribution<double>,n>(*this, uniform_double);}
	template <int n> VarArray<std::normal_distribution<double>,n> norm_array() {return VarArray<std::normal_distribution<double>,n>(*this, normal);}
};

#endif /* UTILS_OMEGA_H_ */
