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
	virtual ~Serializable() = default;
	virtual std::ostream& json(std::ostream& os, int indent = 0) const = 0;
	friend std::ostream& operator<<(std::ostream& os, const Serializable& s);
};

template<typename I>
using if_integral = typename std::enable_if<std::is_integral<I>::value>::type*;
template<typename X>
using if_floating_point = typename std::enable_if<std::is_floating_point<X>::value>::type*;
template<typename S>
using if_serializable = typename std::enable_if<std::is_base_of<Serializable, S>::value>::type*;

// Integer
template<typename I, typename = if_integral<I>>
class Integer: public Serializable {
private:
	I integer_;
public:
	Integer(I i) : integer_(i) {}
	virtual std::ostream& json(std::ostream& os, int indent = 0) const override {
		return os << integer_;
	}
};

// Real
template<typename X, if_floating_point<X> = nullptr>
class Real: public Serializable {
private:
	X real_;
public:
	Real(X x) : real_(x) {}
	virtual std::ostream& json(std::ostream& os, int indent = 0) const override {
		return os << real_;
	}
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
class Object: public std::map<String, std::unique_ptr<Serializable>>, public Serializable {
public:
	virtual std::ostream& json(std::ostream& os, int indent = 0) const override;
	template<typename S, if_serializable<S> = nullptr>
	S& get(std::string key) {
		return *(dynamic_cast<S*>((*this)[key].get()));
	}
	template<typename S, if_serializable<S> = nullptr>
	Object& set(std::string key, S *s) {
		(*this)[key] = std::unique_ptr<Serializable>(dynamic_cast<Serializable*>(s));
		return *this;
	}
	template<typename I, if_integral<I> = nullptr>
	Object& set(std::string key, I i) {
		return set(key, new json::Integer<I>(i));
	}
	template<typename X, if_floating_point<X> = nullptr>
	Object& set(std::string key, X x) {
		return set(key, new json::Real<X>(x));
	}
	Object& set(std::string key, const std::string &s) {
		return set(key, new json::String(s));
	}
	template<typename S, if_serializable<S> = nullptr>
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
	template<typename S, if_serializable<S> = nullptr>
	S& get() {
		return *(dynamic_cast<S*>(back().get()));
	}
	template<typename S, if_serializable<S> = nullptr>
	S& get(int i) {
		return *(dynamic_cast<S*>((*this)[i].get()));
	}
	template<typename S, if_serializable<S> = nullptr>
	Array& add(S *s) {
		push_back(std::unique_ptr<S>(s));
		return *this;
	}
	template<typename I, if_integral<I> = nullptr>
	Array& add(I i) {
		return add(new json::Integer<I>(i));
	}
	template<typename X, if_floating_point<X> = nullptr>
	Array& add(X x) {
		return add(new json::Real<X>(x));
	}
	Array& add(const std::string &s) {
		return add(new String(s));
	}
	template<typename S, if_serializable<S> = nullptr>
	Array& add() {
		push_back(std::unique_ptr<S>(new S()));
		return *this;
	}
	template<typename S, if_serializable<S> = nullptr>
	Array& set(int k, S *s) {
		(*this)[k] = std::unique_ptr<S>(s);
		return *this;
	}
	template<typename I, if_integral<I> = nullptr>
	Array& set(int k, I i) {
		return set(k, new json::Integer<I>(i));
	}
	template<typename X, if_floating_point<X> = nullptr>
			Array& set(int k, X x) {
		return set(k, new json::Real<X>(x));
	}
	Array& set(int k, const std::string &s) {
		return set(k, new json::String(s));
	}
	template<typename S, if_serializable<S> = nullptr>
	Array& set(int k) {
		(*this)[k] = std::unique_ptr<S>(new S());
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
