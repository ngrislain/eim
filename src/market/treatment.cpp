/*
 * treatment.cpp
 *
 *  Created on: 20 août 2018
 *      Author: ngrislain16
 */

#include "treatment.h"

#include <sstream>

using namespace std;
using namespace boost;

ostream& operator<<(ostream& os, const BernoulliTreatment& t){
	os << "BernoulliTreatment(" << endl << "[[" << t.data_[0][0];
	for (BernoulliTreatment::IndexType j=1; j<t.data_.shape()[1]; j++) {
		os << ", " << t.data_[0][j];
	}
	os << "]";
	for (BernoulliTreatment::IndexType i=1; i<t.data_.shape()[0]; i++) {
		os << endl << " [" << t.data_[i][0];
		for (BernoulliTreatment::IndexType j=1; j<t.data_.shape()[1]; j++) {
			os << ", " << t.data_[i][j];
		}
		os << "]";
	}
	os << "])" << endl;
	return os;
}

ostream& operator<<(ostream& os, const CompoundBernoulliTreatment& t){
	os << "CompoundBernoulliTreatment(" << endl << "[[" << t.data_[0][0];
	for (CompoundBernoulliTreatment::IndexType j=1; j<t.data_.shape()[1]; j++) {
		os << ", " << t.data_[0][j];
	}
	os << "]";
	for (CompoundBernoulliTreatment::IndexType i=1; i<t.data_.shape()[0]; i++) {
		os << endl << " [" << t.data_[i][0];
		for (CompoundBernoulliTreatment::IndexType j=1; j<t.data_.shape()[1]; j++) {
			os << ", " << t.data_[i][j];
		}
		os << "]";
	}
	os << "])" << endl;
	return os;
}
