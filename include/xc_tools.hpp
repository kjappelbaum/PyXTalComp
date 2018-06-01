#ifndef XC_TOOLS_H
#define XC_TOOLS_H
#include <Python.h>
#include <xtalcomp/xtalcomp.h>
#include <vector>
#include <map>
#include <string>
#include <iostream>

/** Reads the position array from an atoms object */
void get_positions( PyObject* atoms, std::vector<XcVector> &pos );

/** Converts symbols to types */
void get_types( PyObject *atoms, std::vector<unsigned int> &types, std::map<std::string,unsigned int> &symb_lut );

template<class key,class value>
std::ostream& operator<<(std::ostream& out, const std::map<key,value> &dict )
{
  for (auto iter=dict.begin(); iter != dict.end(); ++iter )
  {
    out << iter->first << ": " << iter->second << "\n";
  }
  return out;
};

template<class type>
std::ostream& operator<<(std::ostream &out, const std::vector<type> &vec )
{
  out << "[";
  for (unsigned int i=0;i<vec.size();i++ )
  {
    out << vec[i] << " ";
  }
  out << "]";
  return out;
};
#endif
