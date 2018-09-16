/*
 * utils.h
 *
 *  Created on: 16 sept. 2018
 *      Author: ngrislain16
 */

#ifndef UTILS_H_
#define UTILS_H_

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
