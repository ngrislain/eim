/*
 * plot.h
 *
 *  Created on: 8 août 2018
 *      Author: ngrislain16
 */

#ifndef UTILS_PLOT_H_
#define UTILS_PLOT_H_

#include <iostream>
#include <algorithm>
#include <array>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <boost/multi_array.hpp>

class Plot {
private:
	boost::python::object main_module;
	boost::python::object main_namespace;
public:
	Plot();
	template<typename V> Plot& plot(V& x, V& y);
	template<typename V> Plot& image(V& im);
};

#endif /* UTILS_PLOT_H_ */
