/*
 * utils.h
 *
 *  Created on: 16 sept. 2018
 *      Author: ngrislain16
 */

#ifndef UTILS_H_
#define UTILS_H_

// Some indexing facilities

template <int... n_0>
class Index;

template <int n_0, int... n>
class Index<n_0, n...> {
public:
	const int index;
	Index(int i=0) : index(i) {};
	inline Index<n...> operator[](int i) {
		return Index<n...>(index*n_0 + i);
	}
};

template <int n>
class Index<n> {
public:
	int index;
	Index(int i=0) : index(i) {};
	inline int operator[](int i) {
		return index*n + i;
	}
};

class Acceptor;

class Visitor {
public:
	void visit(Acceptor &acceptor) {};
};

class ConstVisitor {
public:
	void visit(const Acceptor &acceptor) {};
};

class Acceptor {
public:
	virtual ~Acceptor() = default;
	virtual void accept(Visitor &v) {v.visit(*this);}
	virtual void accept(ConstVisitor &v) const {v.visit(*this);}
};



#endif /* UTILS_H_ */
