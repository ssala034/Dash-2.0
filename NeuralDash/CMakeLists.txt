cmake_minimum_required(VERSION 3.4...3.18)
project(dash_bindings)

add_library(mymath STATIC src/mymath.cpp)
set_target_properties(mymath PROPERTIES POSITION_INDEPENDENT_CODE ON)

#could delpoy set_target cpp files as C++ library
#could create executable for unit testing

add_subdirectory(pybind11)

#will produce a shared library
pybind11_add_module(dash_bindings src/binder.cpp)
