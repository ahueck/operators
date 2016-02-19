[![Build Status](https://travis-ci.org/ahueck/operators.svg?branch=master)](https://travis-ci.org/ahueck/operators)

operators
===========

This is a project for creating user-defined types using operator overloading.


Goal
------------

Multiple user-defined types with different techniques using operator overloading
- Standard operator overloading:
  - [*adouble* header](include/adouble.h)
- Expression templates
- Maximal compatibility (drop-in replacement for a floating-point type)


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
2.  cmake (version >= 2.8)

### Build the unit tests

In the root folder of the project:

    mkdir build && cd build/
    cmake ..
    make

The binary should be created in the project folder *bin*. 
