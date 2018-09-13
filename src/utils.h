/*
 * serialize.h
 *
 *  Created on: 13 sept. 2018
 *      Author: ngrislain16
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>

template <typename Container>
std::ostream& operator<<(std::ostream& os, const Container& c) {
	os << "[";
	std::string sep = "";
	for (typename Container::value_type v : c) {
		os << sep << v;
		sep = ", ";
	}
	os << "]" << std::endl;
	return os;
}

template <>
std::ostream& operator<<(std::ostream& os, const std::string& s) {
	return os << s;
}

#endif /* UTILS_H_ */
