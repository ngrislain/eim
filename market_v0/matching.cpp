/*
 * matching.cpp
 *
 *  Created on: 17 juil. 2018
 *      Author: ngrislain16
 */

#include "../market_v0/matching.h"

#include <sstream>


using namespace std;
using namespace boost;

ostream& operator<<(ostream& os, const BernoulliMatching& m){
	os << "BernoulliMatching(" << endl << "[[" << m.data_[0][0];
	for (BernoulliMatching::IndexType j=1; j<m.data_.shape()[1]; j++) {
		os << ", " << m.data_[0][j];
	}
	os << "]";
	for (BernoulliMatching::IndexType i=1; i<m.data_.shape()[0]; i++) {
		os << endl << " [" << m.data_[i][0];
		for (BernoulliMatching::IndexType j=1; j<m.data_.shape()[1]; j++) {
			os << ", " << m.data_[i][j];
		}
		os << "]";
	}
	os << "])" << endl;
	return os;
}
