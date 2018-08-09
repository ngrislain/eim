/*
 * vector.cpp
 *
 *  Created on: 8 août 2018
 *      Author: ngrislain16
 */

#include "vector.h"

#include <iostream>

using namespace std;
namespace b = boost;

template<typename K, typename V, typename D>
Vector<K,V,D>::Vector(D& d) {
	data = d;
}

template<>
Vector<array<int,2>,double,b::multi_array<double,2>>::Vector(b::multi_array<double,2>& d) : data(d) {
	cout << "Specialized method" << endl;
}

template<typename K, typename V, typename D>
Vector<K,V,D>& Vector<K,V,D>::for_each(void(K,V)) {
	return *this;
}
