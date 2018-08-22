/*
 * tests.cpp
 *
 *  Created on: 13 août 2018
 *      Author: ngrislain16
 */

#include "tests.h"

#include <iostream>
#include <random>
#include <vector>
#include <type_traits>
#include <algorithm>

#include "utils/plot.h"
#include "utils/omega.h"
#include "market/demand.h"
#include "market/matching.h"
#include "market/treatment.h"
#include "market/value.h"
#include "utils/for.h"

Tests::Tests() {
	std::cout << "Running tests" << std::endl;
//	treatment();
//	value();
//	matching();
//	demand();
//	omega();
//	utils_for();
}

void Tests::treatment() {
	std::cout << std::endl <<  "Testing Treatment" << std::endl;
	Plot p;
	Omega o_structure;
	Omega o;

	auto t = o(SplitTreatment(0.5, 0.4, 0.95));
	std::cout << t() << std::endl;

	std::vector<Omega::Ext<Supply>> ss;
	for (int i = 0; i < 100; i++) {
		ss.push_back(o(Supply()));
	}
	std::vector<Omega::Ext<Demand>> ds;
	for (int i = 0; i < 100; i++) {
		ds.push_back(o(Demand()));
	}

	auto s_ord = [&t](Omega::Ext<Supply> &a, Omega::Ext<Supply> &b){return t()(a().id(),0)<t()(b().id(),0);};
	auto d_ord = [&t](Omega::Ext<Demand> &a, Omega::Ext<Demand> &b){return t()(0,a().id())<t()(0,b().id());};
	sort(ss.begin(), ss.end(), s_ord);
	sort(ds.begin(), ds.end(), d_ord);

	boost::multi_array<double, 2> image(boost::extents[100][100]);
	for (int i = 0; i < ss.size(); i++) {
		for (int j = 0; j < ds.size(); j++) {
			image[i][j] = t()(ss[i](), ds[j]());
		}
	}

	p.image(image);
	++o;
	p.image(image);
}

void Tests::value() {
	std::cout << std::endl <<  "Testing Value" << std::endl;
	Plot p;
	Omega o_structure;
	Omega o;

	std::cout << o << std::endl;
	auto v = o(StructuredNoisyValue(StructuredNoisyValue::basic_structure, 10, 10, 0, 0.5));
	std::cout << v() << std::endl;
	std::cout << o << std::endl;

	std::cout << o << std::endl;
	auto s = o(Supply());
	std::cout << s() << std::endl;
	std::cout << o << std::endl;

	std::vector<Omega::Ext<Supply>> ss;
	for (int i = 0; i < 100; i++) {
		ss.push_back(o(Supply()));
	}
	std::vector<Omega::Ext<Demand>> ds;
	for (int i = 0; i < 100; i++) {
		ds.push_back(o(Demand()));
	}

	auto s_ord = [&v](Omega::Ext<Supply> &a, Omega::Ext<Supply> &b){return v()(a().id(),0)<v()(b().id(),0);};
	auto d_ord = [&v](Omega::Ext<Demand> &a, Omega::Ext<Demand> &b){return v()(0,a().id())<v()(0,b().id());};
	sort(ss.begin(), ss.end(), s_ord);
	sort(ds.begin(), ds.end(), d_ord);

	boost::multi_array<double, 2> image(boost::extents[100][100]);
	for (int i = 0; i < ss.size(); i++) {
		for (int j = 0; j < ds.size(); j++) {
			image[i][j] = v()(ss[i](), ds[j]());
		}
	}

	p.image(image);
	std::cout << ss.back()().id() << std::endl;
	std::cout << ds.back()().id() << std::endl;
	std::cout << o << std::endl;
	for (int k=0; k<5; k++) {
		++o;
		sort(ss.begin(), ss.end(), s_ord);
		sort(ds.begin(), ds.end(), d_ord);
		for (int i = 0; i < ss.size(); i++) {
			for (int j = 0; j < ds.size(); j++) {
				image[i][j] = v()(ss[i](), ds[j]());
			}
		}
		p.image(image);
		std::cout << ss.back()().id() << std::endl;
		std::cout << ds.back()().id() << std::endl;
		std::cout << o << std::endl;
	}
}

void Tests::matching() {
	std::cout << std::endl <<  "Testing Matching" << std::endl;
	Plot p;
	Omega o;

	//auto m = o(BernoulliMatching(0.5, 50, 50));
	auto m = o(SplitMatching(0.5, 0.25));
	std::cout << m() << std::endl;

	std::vector<Omega::Ext<Supply>> ss;
	for (int i = 0; i < 100; i++) {
		ss.push_back(o(Supply()));
	}
	std::vector<Omega::Ext<Demand>> ds;
	for (int i = 0; i < 100; i++) {
		ds.push_back(o(Demand()));
	}

	static_assert(std::is_move_assignable<Supply>::value, "Supply not move assignable");
	static_assert(std::is_move_assignable<Omega::Ext<Supply>>::value, "Omega::Ext<Supply> not move assignable");

	auto s_ord = [&m](Omega::Ext<Supply> &a, Omega::Ext<Supply> &b){return m()(a().id(),0)<m()(b().id(),0);};
	auto d_ord = [&m](Omega::Ext<Demand> &a, Omega::Ext<Demand> &b){return m()(0,a().id())<m()(0,b().id());};

	sort(ss.begin(), ss.end(), s_ord);
	sort(ds.begin(), ds.end(), d_ord);

	boost::multi_array<double, 2> image(boost::extents[100][100]);
	for (int i = 0; i < ss.size(); i++) {
		for (int j = 0; j < ds.size(); j++) {
			image[i][j] = m()(ss[i](), ds[j]());
		}
	}

	p.image(image);
	++o;
	p.image(image);
}

void Tests::demand() {
	std::cout << std::endl <<  "Testing Demand" << std::endl;
	Plot p;
	Omega o;
	std::vector<double> x, y;
	auto d = o(Demand());
	for (int i = 0; i < 10000; i++) {
		time_t enter = std::chrono::system_clock::to_time_t(d().enter_date());
		time_t travel = std::chrono::system_clock::to_time_t(d().travel_date());
		x.push_back(enter);
		++o;
		y.push_back(d().id());
//		std::cout << d() << std::endl;
	}
	p.plot(x, y, ", 'ro', alpha=0.5");
}

void Tests::omega() {
	std::cout << std::endl <<  "Testing Omega" << std::endl;
	Omega o(20);
	std::normal_distribution<double> u{2,1};
	std::cout << "o = " << o << std::endl;
	//auto a = o(u);
	auto a = o.var(std::normal_distribution<double>{3,1});
	auto b = o.integer();
	auto c = o.real();
	auto d = o.norm();
	auto e = o.var(std::exponential_distribution<>(0.1));
	auto A = o.iter(u, std::array<double, 5>{});
	std::array<unsigned long, 5> data;
	auto B = o.integer(data);
	auto C = o.real(std::array<double, 5>{});
	auto D = o.norm(std::array<double, 5>{});
	auto E = o.iter(std::exponential_distribution<>(0.01), std::array<double, 10>{});
	std::cout << "o = " << o << std::endl;
	for (int i=0; i<1; i++) {
		auto f = o.real();
		std::cout << "o = " << o << std::endl;
		std::cout << "f = " << f << std::endl;
	}
	std::cout << "o = " << o << std::endl;
	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "a() = " << a() << std::endl;
	std::cout << "b() = " << b() << std::endl;
	std::cout << "c() = " << c() << std::endl;
	std::cout << "d() = " << d() << std::endl;
	for (int i=0; i<10; i++) {
		std::cout << "++o" << std::endl; ++o;
		std::cout << "a = " << a << std::endl;
		std::cout << "b = " << b << std::endl;
		std::cout << "c = " << c << std::endl;
		std::cout << "d = " << d << std::endl;
		std::cout << "e = " << e << std::endl;
		std::cout << "e = " << e << std::endl;
		std::cout << "A = " << A << std::endl;
		std::cout << "A = " << A << std::endl;
		std::cout << "B = " << B << std::endl;
		std::cout << "C = " << C << std::endl;
		std::cout << "D = " << D << std::endl;
		std::cout << "E = " << E << std::endl;
		std::cout << "E = " << E << std::endl;
	}
}

void Tests::utils_for() {
	std::vector<double> a = {1,2,3};
	For<std::vector<double>, int, double>::each(a, [](int i, double x){std::cout << i << ", " << x*x << std::endl;});
}

