/*
 * for_each.h
 *
 *  Created on: 9 août 2018
 *      Author: ngrislain16
 */

#ifndef UTILS_FOR_H_
#define UTILS_FOR_H_

#include <array>
#include <functional>
#include <iostream>
#include <boost/multi_array.hpp>

// Generic For
template<typename D, typename K, typename V>
struct For {
	static V one(D const &d, K const &k) {return d[k];};
	static void one(D const &d, K const &k, std::function<void(V)> f) {f(d[k]);};
	static void each(D const &d, std::function<void(K, V)> f) {
		int k = 0;
		std::for_each(d.begin(), d.end(), [&k,&f](V v){f(k++, v);});
	};
};

// For multi_array
template<typename T, int n>
struct For<boost::multi_array<T, n>, std::array<int, n>, double> {
	static double one(boost::multi_array<T, n> const &d, std::array<int, n> const &k) {return d(k);};
	static void one(boost::multi_array<T, n> const &d, std::array<int, n> const &k, std::function<void(double)> f) {f(d(k));};
	static void each(boost::multi_array<T, n> const &d, std::function<void(std::array<int, n>, double)> f) {
		std::array<int, n> indices;
		for (int i=0; i<d.num_elements(); i++) {
			for (int k=0; k < d.num_dimensions(); k++) {
				indices[k] = (i / d.strides()[k] % d.shape()[k] + d.index_bases()[k]);
			}
			f(indices, d.data()[i]);
		}
	};
};

// For simple array
template<typename T, int n>
struct For<std::array<T, n>, int, double> {
	static double one(std::array<T, n> const &d, int const &k) {return d[k];};
	static void one(std::array<T, n> const &d, int const &k, std::function<void(double)> f) {f(d[k]);};
	static void each(std::array<T, n> const &d, std::function<void(int, double)> f) {
		for (int i=0; i<d.size(); i++) {
			f(i, d[i]);
		}
	};
};

#endif /* UTILS_FOR_H_ */
