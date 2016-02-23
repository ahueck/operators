/*
 * test_adouble_h.h
 *
 *  Created on: Nov 16, 2015
 *      Author: ahueck
 */


#include <cpp03/adouble.h>

#include <TestUtil.h>

#define CATCH_CONFIG_MAIN
#include <catch/catch.hpp>

#define u_type adouble

SCENARIO("Overloaded Arithmetic Operator Test", "[operator]") {
  GIVEN("Two operands of type adouble a, b") {
    u_type a = 10.0;
    u_type b = 2.0;

    REQUIRE(a.value() == 10.0);
    REQUIRE(b.value() == 2.0);

    _test_2_t(+, 12.0)
    _test_2_t(-, 8.0)
    _test_2_t(*, 20.0)
    _test_2_t(/, 5.0)

    _test_1_t(+, 12.0)
    _test_1_t(-, 8.0)
    _test_1_t(*, 20.0)
    _test_1_t(/, 5.0)
  }
}

SCENARIO("Overloaded Boolean Operator Test", "[bool_operator]") {
  GIVEN("Two operands of type adouble a, b") {
    u_type a = 10.0;
    u_type b = 2.0;

    REQUIRE(a.value() == 10.0);
    REQUIRE(b.value() == 2.0);

    _test_2_t(==, false)
    _test_2_t(!=, true)
    _test_2_t(>, true)
    _test_2_t(<, false)
    _test_2_t(>=, true)
    _test_2_t(<=, false)
  }
}

SCENARIO("Unary Operator Test", "[unary_operator]") {
  GIVEN("Two operands of type adouble a, b") {
    u_type a = 10.0;

    REQUIRE(a.value() == 10.0);
  }
}
