/*
 * serialize.h
 *
 *  Created on: 13 sept. 2018
 *      Author: ngrislain16
 */

#ifndef JSON_H_
#define JSON_H_

#include <iostream>
#include <memory>
#include <map>
#include <vector>
#include <type_traits>

namespace json {
// An interface for a Json Serializable object
class Serializable {
public:
//	Serializable() = default;
//	Serializable(const Serializable &s) = default;
//	Serializable& operator=(const Serializable &s) = default;
	virtual ~Serializable() = default;
	virtual std::ostream& json(std::ostream& os, int indent = 0) const = 0;
	friend std::ostream& operator<<(std::ostream& os, const Serializable& s);
};

template<typename N>
using if_arithmetic = typename std::enable_if<std::is_arithmetic<N>::value>::type;
template<typename S>
using if_serializable = typename std::enable_if<std::is_base_of<Serializable, S>::value>::type;

// Number
class Number: public Serializable {
private:
	double number_;
public:
	Number(double n) :
			number_(n) {
	}
	operator double() const {
		return number_;
	}
	virtual std::ostream& json(std::ostream& os, int indent = 0) const override;
};

// String
class String: public std::string, public Serializable {
public:
	String(const std::string s) :
			std::string(s) {
	}
	virtual std::ostream& json(std::ostream& os, int indent = 0) const override;
};

// Object
class Object: public std::map<String, std::unique_ptr<Serializable>>,
		public Serializable {
public:
	virtual std::ostream& json(std::ostream& os, int indent = 0) const override;
	template<typename S, typename = if_serializable<S>>
	S& get(std::string key) {
		return *(dynamic_cast<S*>((*this)[key].get()));
	}
	template<typename S, typename = if_serializable<S>>
	Object& set(std::string key, S *s) {
		(*this)[key] = std::unique_ptr<Serializable>(dynamic_cast<Serializable*>(s));
		return *this;
	}
	template<typename N, typename = if_arithmetic<N>>
	Object& set(std::string key, N n) {
		return set(key, new json::Number(n));
	}
	Object& set(std::string key, const std::string &s) {
		return set(key, new json::String(s));
	}
	template<typename S, typename = if_serializable<S>>
	Object& set(std::string key) {
		(*this)[key] = std::unique_ptr<S>(new S());
		return *this;
	}
	;
};

class Array: public std::vector<std::unique_ptr<Serializable>>,
		public Serializable {
public:
	virtual std::ostream& json(std::ostream& os, int indent = 0) const override;
	template<typename S, typename = if_serializable<S>>
	S& get() {
		return *(dynamic_cast<S*>(back().get()));
	}
	template<typename S, typename = if_serializable<S>>
	S& get(int i) {
		return *(dynamic_cast<S*>((*this)[i].get()));
	}
	template<typename S, typename = if_serializable<S>>
	Array& add(S *s) {
		push_back(std::unique_ptr<S>(s));
		return *this;
	}
	template<typename N, typename = if_arithmetic<N>>
	Array& add(N n) {
		return add(new Number(n));
	}
	Array& add(const std::string &s) {
		return add(new String(s));
	}
	template<typename S, typename = if_serializable<S>>
	Array& add() {
		push_back(std::unique_ptr<S>(new S()));
		return *this;
	}
	template<typename S, typename = if_serializable<S>>
	Array& set(int i, S *s) {
		(*this)[i] = std::unique_ptr<S>(s);
		return *this;
	}
	template<typename N, typename = if_arithmetic<N>>
	Array& set(int i, N n) {
		return set(i, new json::Number(n));
	}
	Array& set(int i, const std::string &s) {
		return set(i, new json::String(s));
	}
	template<typename S, typename = if_serializable<S>>
	Array& set(int i) {
		(*this)[i] = std::unique_ptr<S>(new S());
		return *this;
	}
};

class Bool: public Serializable {
private:
	bool bool_;
public:
	Bool(bool b) :
			bool_(b) {
	}
	operator bool() const {
		return bool_;
	}
	virtual std::ostream& json(std::ostream& os, int indent = 0) const override;
};

class Null: public Serializable {
public:
	Null() {
	}
	operator void*() const {
		return nullptr;
	}
	virtual std::ostream& json(std::ostream& os, int indent = 0) const override;
};
}

#endif /* JSON_H_ */
