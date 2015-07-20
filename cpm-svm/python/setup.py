from distutils.core import setup, Extension
from Cython.Build import cythonize

setup(ext_modules = cythonize(Extension(
           "cython_svm",                                # the extesion name
           sources=["cython_svm.pyx", "src/data.cpp", "src/svm.cpp", "src/solve_qp.cpp"], # the Cython source and additional C++ source files
           language="c++",                        # generate and compile C++ code
      )))
