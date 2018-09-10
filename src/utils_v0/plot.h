/*
 * plot.h
 *
 *  Created on: 8 août 2018
 *      Author: ngrislain16
 */

#ifndef UTILS_V0_PLOT_H_
#define UTILS_V0_PLOT_H_

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <array>
#include <boost/python.hpp>
#include <boost/python/numpy.hpp>
#include <boost/multi_array.hpp>

#include "../utils_v0/for.h"

class Plot {
private:
	boost::python::object main_module;
	boost::python::object main_namespace;
public:
	Plot();
	// Plot y vs x
	template<typename V> void plot(V const &x, V const &y, std::string const &args="") {
		try {
			boost::python::list x_data;
			For<V, int, double>::each(x, [&x_data](int k, double v) {
								x_data.append(v);
							});
			boost::python::numpy::ndarray x_array = boost::python::numpy::array(x_data);
			main_namespace["x_array"] = x_array;
			boost::python::list y_data;
			For<V, int, double>::each(y, [&y_data](int k, double v) {
								y_data.append(v);
							});
			boost::python::numpy::ndarray y_array = boost::python::numpy::array(y_data);
			main_namespace["y_array"] = y_array;
			std::stringstream code;
			code << "plt.plot(x_array, y_array" << args << ")\n" <<
					"plt.show()\n";
			boost::python::object ignored = boost::python::exec(code.str().c_str(), main_namespace);
		} catch (const boost::python::error_already_set& e) {
			PyErr_Print();
		}
	};
	// Plot y vs index
	template<typename V> void plot(V const &y, std::string const &args="") {
		try {
			boost::python::list x_data, y_data;
			For<V, int, double>::each(y, [&x_data, &y_data](int k, double v) {
								x_data.append(k);
								y_data.append(v);
							});
			boost::python::numpy::ndarray x_array = boost::python::numpy::array(x_data);
			boost::python::numpy::ndarray y_array = boost::python::numpy::array(y_data);
			main_namespace["x_array"] = x_array;
			main_namespace["y_array"] = y_array;
			std::stringstream code;
			code << "plt.plot(x_array, y_array" << args << ")\n" <<
					"plt.show()\n";
			boost::python::object ignored = boost::python::exec(code.str().c_str(), main_namespace);
		} catch (const boost::python::error_already_set& e) {
			PyErr_Print();
		}
	};
	// Plot images
	template<typename V> void image(V const &im, std::string const &args="") {
		try {
			boost::python::tuple shape = boost::python::make_tuple((int)im.shape()[0], (int)im.shape()[1]);
			boost::python::list data;
			For<V, std::array<int, 2>, double>::each(im, [&data](std::array<int,2> k, double v) {
								data.append(v);
							});
			boost::python::numpy::ndarray ndarray = boost::python::numpy::array(data);
			ndarray = ndarray.reshape(shape);
			main_namespace["shape"] = shape;
			main_namespace["ndarray"] = ndarray;
			std::stringstream code;
			code << "plt.imshow(ndarray" << args << ")\n" <<
					"plt.show()\n";
			boost::python::object ignored = boost::python::exec(code.str().c_str(), main_namespace);
		} catch (const boost::python::error_already_set& e) {
			PyErr_Print();
		}
	};
};

#endif /* UTILS_V0_PLOT_H_ */
