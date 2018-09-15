/*
 * main.cpp
 *
 *  Created on: 17 juil. 2018
 *      Author: ngrislain16
 */
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>

#include "tests.h"

using namespace std;

int main() {
	tests::json();
	tests::omega();
	tests::market();
	return 0;
}
