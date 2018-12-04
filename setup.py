from setuptools import setup, Extension

module1 = Extension( "pyxtalcomp_cpp", sources=["src/pyxtalcomp.cpp","src/xc_tools.cpp"],
include_dirs=["include","/home/kevin/Downloads/XtalComp-master"], extra_compile_args=['-std=c++11'], language="c++",
libraries=["XtalComp"], library_dirs=["/home/kevin/Downloads/XtalComp-master/build"])

setup(
    name="pyxtalcomp",
    ext_modules=[module1]
)
