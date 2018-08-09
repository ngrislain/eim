/*
 * vector.h
 *
 *  Created on: 8 août 2018
 *      Author: ngrislain16
 */

#ifndef UTILS_VECTOR_H_
#define UTILS_VECTOR_H_

#include <array>
#include <functional>
#include <iostream>
#include <boost/multi_array.hpp>

template<typename K, typename V, typename D>
class Vector {
private:
	D& data;
public:
	Vector(D& d) : data(d) {}
	Vector(D&& d) : data(d) {}
	void for_each(std::function<void(K, V)>);
};

/*Template specialization*/

template<int n, typename T>
class Vector<std::array<int, n>, double, boost::multi_array<T, n>> {
	typedef boost::multi_array<T, n> NDArray;
	typedef typename NDArray::index Index;
	typedef std::array<int, n> Indices;
private:
	NDArray& data;
public:
	Vector(NDArray& d) : data(d) {}
	Vector(NDArray&& d) : data(d) {}

	void for_each(std::function<void(Indices, double)>) {
		for (int i=0; i<data.num_elements(); i++) {
			std::cout << *(data.origin()+i) << " " << indices(data.origin()+i)[0] << std::endl;
		}
	}

	Index index(const T* element, const int direction) {
		int offset = element - data.origin();
		return (offset / data.strides()[direction] % data.shape()[direction]
				+ data.index_bases()[direction]);
	}

	Indices indices(const T* element) {
		Indices indices;
		for (int dir = 0; dir < data.num_dimensions(); dir++) {
			indices[dir] = index(element, dir);
		}
		return indices;
	}
};

#endif /* UTILS_VECTOR_H_ */
