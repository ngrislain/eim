/*
 * omega.h
 *
 *  Created on: 13 août 2018
 *      Author: ngrislain16
 */

#ifndef UTILS_OMEGA_H_
#define UTILS_OMEGA_H_

#include <string>
#include <limits>
#include <random>
#include <functional>

class Omega {
private:
	unsigned long state_;
	std::mt19937_64 generator_;
	Omega();
	Omega(const Omega &) = delete;
	Omega(const Omega &&) = delete;
public:
	typedef unsigned long result_type;
	static constexpr unsigned long min() {return std::numeric_limits<unsigned long>::min();};
	static constexpr unsigned long max() {return std::numeric_limits<unsigned long>::max();};
	static std::mt19937_64 generator;
	static Omega instance;
	unsigned long operator()() const;
	Omega& operator++();

	template <typename G>
	class Generator {
	private:
		const G &generator_;
		const unsigned long state_;
	public:
		typedef unsigned long result_type;
		static constexpr unsigned long min() {return Omega::min();};
		static constexpr unsigned long max() {return Omega::max();};
		Generator(const G &g, const unsigned long s) : generator_(g), state_(s) {}
		Generator(const G &g, const std::string s) : generator_(g), state_(std::hash<std::string>()(s)) {}
		unsigned long operator()() const {
			Omega::generator.seed(generator_()+state_);
			return Omega::generator();
		}
		Generator<Generator<G>> operator[](const unsigned long s) {
			return Generator<Generator<G>>(*this, s);
		}
		Generator<Generator<G>> operator[](const std::string s) {
			return Generator<Generator<G>>(*this, s);
		}
	};

	Generator<Omega> operator[](const unsigned long s);
	Generator<Omega> operator[](const std::string s);
};

#endif /* UTILS_OMEGA_H_ */
