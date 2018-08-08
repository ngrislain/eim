/*
 * vector.h
 *
 *  Created on: 8 août 2018
 *      Author: ngrislain16
 */

#ifndef UTILS_VECTOR_H_
#define UTILS_VECTOR_H_

#include <array>
#include <boost/multi_array.hpp>

template<typename K, typename V, typename D>
class Vector {
private:
	D& data;
public:
	Vector(D& data);
	Vector& for_each(void(K,V));
};

//template<>
//Vector<std::array<int,2>,double,boost::multi_array<int,2>>::Vector(boost::multi_array<int,2>& d);

#endif /* UTILS_VECTOR_H_ */
