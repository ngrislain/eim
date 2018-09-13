/*
 * plot.cpp
 *
 *  Created on: 8 août 2018
 *      Author: ngrislain16
 */

#include "../utils_v0/plot.h"

#include "../utils_v0/for.h"

using namespace std;
namespace b = boost;
namespace p = boost::python;
namespace np = boost::python::numpy;

// Build the tools to plot any collection
Plot::Plot() {
	Py_Initialize();
	np::initialize();
	try {
		main_module = p::import("__main__");
		main_namespace = main_module.attr("__dict__");
		p::object ignored = boost::python::exec("import matplotlib as mpl\n"
				"mpl.use('TkAgg')\n"
				"import matplotlib.pyplot as plt\n"
				, main_namespace);
	} catch (const boost::python::error_already_set& e) {
		PyErr_Print();
	}
}
