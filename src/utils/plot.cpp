/*
 * plot.cpp
 *
 *  Created on: 8 août 2018
 *      Author: ngrislain16
 */

#include "plot.h"
#include "../demand.h"

namespace b = boost;
namespace p = boost::python;
namespace np = boost::python::numpy;

Plot::Plot() {
	Py_Initialize();
	np::initialize();
	main_module = p::import("__main__");
	main_namespace = main_module.attr("__dict__");

	p::list unif { };
	for (int i = 0; i < 1000; i++) {
		Demand d;
		unif.append(d.rand());
	}
	np::ndarray nda = np::array(unif);
	main_namespace["unif"] = unif;
	main_namespace["nda"] = nda;
//	try {
//		p::object ignored = p::exec("import matplotlib as mpl\n"
//				"mpl.use('TkAgg')\n"
//				"import matplotlib.pyplot as plt\n"
//				"plt.plot(nda)\n"
//				"plt.show()\n", main_namespace);
//	} catch (const p::error_already_set& e) {
//		PyErr_Print();
//	}
}

template<typename V> Plot& Plot::plot(V& x, V& y) {
	return *this;
}

template<typename V> Plot& Plot::image(V& im) {
	return *this;
}

//template<typename T>
//Plot& Plot::image<b::multi_array<T,2>>(b::multi_array<T,2>& im) {
//	std::cout << im.shape() << std::endl;
//	for (b::multi_array<T,2>::index i=0; i<im.shape()[0]; i++) {
//		for (b::multi_array<T,2>::index j=0; j<im.shape()[1]; j++) {
//			std::cout << ", " << im[i][j];
//		}
//	}
//	return *this;
//}
