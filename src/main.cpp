/*
 * main.cpp
 *
 *  Created on: 17 juil. 2018
 *      Author: ngrislain16
 */
#include <iostream>
#include <fstream>
#include "tests.h"
#include "market.h"
#include "json.h"

using namespace std;

int main() {
//	tests::json();
//	tests::omega();
//	tests::market();
//	tests::value();
//	tests::modifier();
//	tests::utils();

	market::Experiment experiment{};
	json::Array results;
	for (int k=0; k<100; k++) {
		std::cout << "Run #" << k << std::endl;
		results.add<market::Result>(new market::Result(experiment.run(100, 0.0+1.0*k/100.0)));
	}
	std::cout << results << std::endl;
	std::system("mkdir /tmp/eim");
	std::ofstream file;
	file.open("/tmp/eim/gmv.json", std::ofstream::out);
	file << results << std::endl;
	file.close();
	return 0;
}
