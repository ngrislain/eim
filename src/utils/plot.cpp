/*
 * plot.cpp
 *
 *  Created on: 8 août 2018
 *      Author: ngrislain16
 */

#include "plot.h"
#include "for.h"
#include "../demand.h"

using namespace std;
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
	main_namespace["unif"] = unif;
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
