/*
 * serialize.h
 *
 *  Created on: 13 sept. 2018
 *      Author: ngrislain16
 */

#ifndef JSON_H_
#define JSON_H_

#include <iostream>
#include <map>
#include <list>

namespace json {
	using number = double;
	using string = std::string;
	template <typename T>
	using object = std::map<string, T>;
	template <typename T>
	using array = std::list<T>;
	enum {null};
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const json::array<T> a) {
	json::string separator = "";
	os << "[";
	for (T v : a) {
		os << separator << v;
		separator = ", ";
	}
	os << "]";
	return os;
}

#endif /* JSON_H_ */
