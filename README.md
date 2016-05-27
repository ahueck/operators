[![Build Status](https://travis-ci.org/ahueck/operators.svg?branch=master)](https://travis-ci.org/ahueck/operators)

operators
===========

This is a project for creating user-defined types using operator overloading.


Project Goals
------------

Provides multiple user-defined types with different techniques employing operator overloading.
- Standard operator overloading (C++98 / C++03):
  - [*adouble* header](include/cpp03/adouble.h)
- Expression templates (C++11):
  - [*adouble_et* header](include/cpp11/adouble_et.h)
- [The Art of C++ / Operators](https://github.com/taocpp/operators) implementation (C++11):
  - [*adouble_tao* header](include/cpp11/adouble_tao.h)

Maximal compatibility with built-in floating-point types 
- *Drop-in replacement*


License
------------

Distributed under the MIT License. For details refer to the [LICENSE](LICENSE)


Installation 
------------

The user-defined types are header based.
The unit tests can be compiled and executed. The Project is only tested on Linux.
For Ubuntu/Debian, refer to the [Travis CI file](.travis.yml) for guidance.

### Prerequisites

1.  C++ Compiler with C++11 support for unit tests (GCC version >= 4.8)
2.  CMake (version >= 2.8)

### Build the unit tests

In the root folder of the project:

    mkdir build && cd build/
    cmake ..
    make

The binary should be created in the project folder *bin*. 
