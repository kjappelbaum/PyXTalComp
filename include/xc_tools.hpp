#ifndef XC_TOOLS_H
#define XC_TOOLS_H
#include <Python.h>
#include <xtalcomp/xtalcomp.h>
#include <vector>

/** Reads the position array from an atoms object */
void get_positions( PyObject* atoms, std::vector<XcVector> &pos );

/** Converts symbols to types */
void get_types( PyObject *atoms, std::vector<unsigned int> &types );
#endif
