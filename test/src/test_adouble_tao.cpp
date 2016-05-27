/*
 * test_adouble_tao.cpp
 *
 *  Created on: May 27, 2016
 *      Author: ahueck
 */

#include <cpp11/adouble_tao.h>

#include <TestUtil.h>
// Due to name clashes with cpp03 -> separate TU is created
#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#define OO_TYPE adouble
#define TEST_PREFIX "cpp11adouble_tao_"
#include "operator_test.hpp"
