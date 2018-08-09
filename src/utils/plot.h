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

#include "for.h"

class Plot {
private:
	boost::python::object main_module;
	boost::python::object main_namespace;
public:
	Plot();
	template<typename V> void plot(V const &x, V const &y) {
	}
	;
	template<typename V> void image(V const &im) {
		try {
			boost::python::tuple shape = boost::python::make_tuple((int)im.shape()[0], (int)im.shape()[1]);
			boost::python::list data;
			For<V, std::array<int, 2>, double>::each(im,
							[&data](std::array<int,2> k, double v) {
								data.append(v);
								std::cout << k[0] << ", " << k[1] << " : " << v << std::endl;
							});
			boost::python::numpy::ndarray ndarray = boost::python::numpy::array(data);
			ndarray = ndarray.reshape(shape);
			main_namespace["shape"] = shape;
			main_namespace["ndarray"] = ndarray;
			boost::python::object ignored = boost::python::exec("import matplotlib as mpl\n"
					"mpl.use('TkAgg')\n"
					"import matplotlib.pyplot as plt\n"
					"plt.imshow(ndarray)\n"
					"plt.show()\n", main_namespace);
		} catch (const boost::python::error_already_set& e) {
			PyErr_Print();
		}
	}
};

#endif /* UTILS_PLOT_H_ */
