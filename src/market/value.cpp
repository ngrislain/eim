/*
 * value.cpp
 *
 *  Created on: 14 août 2018
 *      Author: ngrislain16
 */

#include "value.h"

#include <array>

using namespace std;
namespace b = boost;

const StructuredNoisyValue::DataType StructuredNoisyValue::basic_structure([](){
	double data[4][4] = {
			{ 1, 1, 0, -1 },
			{ 1, 1, 0, -1 },
			{ 0, 0, 1, 0 },
			{ -1, -1, 0, 1 }};
	b::multi_array<double, 2> result(b::extents[4][4]);
	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			result[i][j] = 2*data[i][j]-1;
		}
	}
	return result;
}());




