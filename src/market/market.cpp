/*
 * market.cpp
 *
 *  Created on: 21 août 2018
 *      Author: ngrislain16
 */

#include "market.h"

#include "utils/plot.h"
#include "utils/omega.h"
#include "market/demand.h"
#include "market/matching.h"
#include "market/value.h"
#include "market/treatment.h"

void Market::experiment() {
	Omega o;
	// Value matrix
	auto v = o(Value(Value::basic_structure, 10, 10, 0, 1));
	// Treatment matrix
	auto t = o(SplitTreatment(0.5, 0.4, 1));
	// Matching matrix
	auto m = o(FullMatching());
}

