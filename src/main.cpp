/*
 * main.cpp
 *
 *  Created on: 17 juil. 2018
 *      Author: ngrislain16
 */
#include <iostream>
#include "tests.h"
#include "market.h"

using namespace std;

int main() {
//	tests::json();
//	tests::omega();
//	tests::market();
//	tests::value();
//	tests::modifier();
//	tests::utils();

	market::Experiment experiment{};
	experiment.run();
	return 0;
}
