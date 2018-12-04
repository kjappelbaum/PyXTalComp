#include <xtalcomp.h>
#include "xc_tools.hpp"
#include <Python.h>
#include <numpy/ndarrayobject.h>
#include <vector>
#include <iostream>
#include <map>
#include <string>

using namespace std;

static PyObject* compare_xtalcomp( PyObject *self, PyObject *args )
{
  PyObject* pos1=nullptr;
  PyObject* pos2=nullptr;
  PyObject* symbs1=nullptr;
  PyObject* symbs2=nullptr;
  PyObject* cell1_raw=nullptr;
  PyObject* cell2_raw=nullptr;
  double cart_tol;
  double ang_tol;
  int reduce_to_primitive=0;

  if ( !PyArg_ParseTuple( args, "OOOOOOddi", &pos1, &pos2, &symbs1, &symbs2, &cell1_raw, &cell2_raw, &cart_tol, &ang_tol, &reduce_to_primitive) )
  {
    PyErr_SetString( PyExc_TypeError, "Could not parse arguments" );
    return NULL;
  }

  char* format = NULL;
  // Read relevant data from the first atoms object
  PyObject *cell1 = PyArray_FROM_OTF( cell1_raw, NPY_DOUBLE, NPY_ARRAY_IN_ARRAY );
  PyObject* cell2 = PyArray_FROM_OTF( cell2_raw, NPY_DOUBLE, NPY_ARRAY_IN_ARRAY );

  // Create XtalComps data structures
  double cell1_c_array[3][3];
  double cell2_c_array[3][3];
  for (unsigned int i=0;i<3;i++ )
  for (unsigned int j=0;j<3;j++ )
  {
    cell1_c_array[i][j] = *static_cast<double*>(PyArray_GETPTR2(cell1,i,j));
    cell2_c_array[i][j] = *static_cast<double*>(PyArray_GETPTR2(cell2,i,j));
  }
  XcMatrix xc_cell1(cell1_c_array);
  XcMatrix xc_cell2(cell2_c_array);
  vector<XcVector> xc_pos1;
  vector<XcVector> xc_pos2;
  vector<unsigned int> types1;
  vector<unsigned int> types2;
  map<string,unsigned int> symb_lut;
  get_positions(pos1, xc_pos1);
  get_positions(pos2, xc_pos2);
  get_types(symbs1, types1, symb_lut);
  get_types(symbs2, types2, symb_lut);

  bool match = XtalComp::compare(xc_cell1, types1, xc_pos1,
                                 xc_cell2, types2, xc_pos2,
                                 NULL, cart_tol, ang_tol, reduce_to_primitive);

  Py_DECREF(cell1);
  Py_DECREF(cell2);
  if ( match )
  {
    Py_RETURN_TRUE;
  }
  Py_RETURN_FALSE;
}

static PyMethodDef pyxtalcomp_methods[] = {
  {"compare_xtalcomp", compare_xtalcomp, METH_VARARGS, "Use XtalComp to compare structures"},
  {NULL,NULL,0,NULL}
};

#if PY_MAJOR_VERSION >= 3
  static struct PyModuleDef pyxtalcomp = {
    PyModuleDef_HEAD_INIT,
    "pyxtalcomp_cpp",
    "this is the python 3 version", 
    -1,
    pyxtalcomp_methods
  };
#endif

#if PY_MAJOR_VERSION >= 3
  PyMODINIT_FUNC PyInit_pyxtalcomp_cpp(int)
  {
    PyObject* module = PyModule_Create( &pyxtalcomp);
    import_array();
    return module;
  };
#else
  PyMODINIT_FUNC initpyxtalcomp_cpp(void)
  {
    Py_InitModule3( "pyxtalcomp_cpp", pyxtalcomp_methods, "This the Python 2 version" );
    import_array();
  };
#endif
