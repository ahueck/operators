/*
 * operator_test.hpp
 *
 *  Created on: May 20, 2016
 *      Author: ahueck
 */

#ifndef TEST_PREFIX
#error Need prefix for the test tags
#endif

#ifndef OO_TYPE
#error Need name of the operator overloading class
#endif

SCENARIO("Overloaded Arithmetic Operator Test", "["  TEST_PREFIX "operator]") {
  GIVEN("Two operands of type " T_STRINGIFY(OO_TYPE) " a, b") {
    OO_TYPE a = 10.0;
    OO_TYPE b = 2.0;

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

SCENARIO("Overloaded Boolean Operator Test", "[" TEST_PREFIX "bool_operator]") {
  GIVEN("Two operands of type " T_STRINGIFY(OO_TYPE) " a, b") {
    OO_TYPE a = 10.0;
    OO_TYPE b = 2.0;

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

SCENARIO("Unary Operator Test", "[" TEST_PREFIX "unary_operator]") {
  GIVEN("An operand of type " T_STRINGIFY(OO_TYPE) " a") {
    OO_TYPE a = 10.0;

    REQUIRE(a.value() == 10.0);

    _test_unary_t(++a, 11.0);
    _test_unary_t(a++, 11.0);
    _test_unary_t(--a, 9.0);
    _test_unary_t(a--, 9.0);
    WHEN("-a") {
      OO_TYPE neg_a = -a;
      THEN("Value is negated") {
        REQUIRE(neg_a.value() == -10.0);
      }
    }
  }
}

#undef TEST_PREFIX
#undef OO_TYPE