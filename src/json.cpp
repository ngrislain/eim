/*
 * serialize.cpp
 *
 *  Created on: 13 sept. 2018
 *      Author: ngrislain16
 */

#include "json.h"
#include <utility>

std::ostream& json::operator<<(std::ostream& os, const json::Serializable& s) {
	return s.json(os);
}

std::ostream& json::String::json(std::ostream& os, int indent) const {
	return os << "\"" << static_cast<std::string>(*this) << "\"";
}

std::ostream& json::Object::json(std::ostream& os, int indent) const {
	std::string separator = "";
	os << "{";
	for (const std::pair<const String, const std::unique_ptr<Serializable>&> &kv : *this) {
		os << separator << std::endl;
		for (int i = 0; i < indent + 1; i++) {
			os << "  ";
		}
		os << kv.first << ":";
		kv.second->json(os, indent + 1);
		separator = ",";
	}
	os << std::endl;
	for (int i = 0; i < indent; i++) {
		os << "  ";
	}
	os << "}";
	return os;
}

template<>
json::Object& json::Object::set<bool>(std::string key, bool b) {
	return set(key, new Bool(b));
}

std::ostream& json::Array::json(std::ostream& os, int indent) const {
	std::string separator = "";
	os << "[";
	for (const std::unique_ptr<Serializable> &s : *this) {
		os << separator << *s;
		separator = ", ";
	}
	os << "]";
	return os;
}

template<>
json::Array& json::Array::add<bool>(bool b) {
	return add(new Bool(b));
}

template<>
json::Array& json::Array::set<bool>(int i, bool b) {
	return set(i, new Bool(b));
}

std::ostream& json::Bool::json(std::ostream& os, int indent) const {
	if (bool_) {
		return os << "true";
	} else {
		return os << "false";
	}
}

std::ostream& json::Null::json(std::ostream& os, int indent) const {
	return os << "null";
}
