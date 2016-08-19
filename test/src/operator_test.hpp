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

SCENARIO("Overloaded Arithmetic Operator Test with class: " T_STRINGIFY(OO_TYPE), "[" TEST_PREFIX "operator]") {
  GIVEN("Two operands of type " T_STRINGIFY(OO_TYPE) " a, b") {
    OO_TYPE a = 10.0;
    OO_TYPE b = 2.0;

    REQUIRE(a.value() == 10.0);
    REQUIRE(b.value() == 2.0);
    // clang-format off
    OP_Test_2_t(+, 12.0)
    OP_Test_2_t(-, 8.0)
    OP_Test_2_t(*, 20.0)
    OP_Test_2_t(/, 5.0)

    OP_Test_1_t(+, 12.0)
    OP_Test_1_t(-, 8.0)
    OP_Test_1_t(*, 20.0)
    OP_Test_1_t(/, 5.0)
    // clang-format on
  }
}

SCENARIO("Overloaded Arithmetic Operator Test with class (rhs): " T_STRINGIFY(OO_TYPE),
         "[" TEST_PREFIX "operator_rhs]") {
  GIVEN("Two operands of mixed types a, b (double)") {
    OO_TYPE a = 10.0;
    double b = 2.0;

    REQUIRE(a.value() == 10.0);
    REQUIRE(b == 2.0);
    // clang-format off
    OP_Test_2_t(+, 12.0)
    OP_Test_2_t(-, 8.0)
    OP_Test_2_t(*, 20.0)
    OP_Test_2_t(/, 5.0)

    OP_Test_1_t(+, 12.0)
    OP_Test_1_t(-, 8.0)
    OP_Test_1_t(*, 20.0)
    OP_Test_1_t(/, 5.0)
    // clang-format on
  }
}

SCENARIO("Overloaded Arithmetic Operator Test with class (lhs): " T_STRINGIFY(OO_TYPE),
         "[" TEST_PREFIX "operator_lhs]") {
  GIVEN("Two operands of mixed types a (double), b") {
    double a = 10.0;
    OO_TYPE b = 2.0;

    REQUIRE(a == 10.0);
    REQUIRE(b.value() == 2.0);
    // clang-format off
    OP_Test_2_t(+, 12.0)
    OP_Test_2_t(-, 8.0)
    OP_Test_2_t(*, 20.0)
    OP_Test_2_t(/, 5.0)
    // clang-format on

    // No binary assignment possible, e.g., "double+=adouble"
  }
}

SCENARIO("Overloaded Boolean Operator Test with class: " T_STRINGIFY(OO_TYPE), "[" TEST_PREFIX "bool_operator]") {
  GIVEN("Two operands of type " T_STRINGIFY(OO_TYPE) " a, b") {
    OO_TYPE a = 10.0;
    OO_TYPE b = 2.0;

    REQUIRE(a.value() == 10.0);
    REQUIRE(b.value() == 2.0);
    // clang-format off
    OP_Test_2_t(==, false)
    OP_Test_2_t(!=, true)
    OP_Test_2_t(>, true)
    OP_Test_2_t(<, false)
    OP_Test_2_t(>=, true)
    OP_Test_2_t(<=, false)
    // clang-format on
  }
}

SCENARIO("Overloaded Boolean Operator Test with class (rhs): " T_STRINGIFY(OO_TYPE),
         "[" TEST_PREFIX "bool_operator_rhs]") {
  GIVEN("Two operands of mixed types a, b (double)") {
    OO_TYPE a = 10.0;
    double b = 2.0;

    REQUIRE(a.value() == 10.0);
    REQUIRE(b == 2.0);
    // clang-format off
    OP_Test_2_t(==, false)
    OP_Test_2_t(!=, true)
    OP_Test_2_t(>, true)
    OP_Test_2_t(<, false)
    OP_Test_2_t(>=, true)
    OP_Test_2_t(<=, false)
    // clang-format on
  }
}

SCENARIO("Overloaded Boolean Operator Test with class (lhs): " T_STRINGIFY(OO_TYPE),
         "[" TEST_PREFIX "bool_operator_lhs]") {
  GIVEN("Two operands of mixed types a (double), b") {
    double a = 10.0;
    OO_TYPE b = 2.0;

    REQUIRE(a == 10.0);
    REQUIRE(b.value() == 2.0);
    // clang-format off
    OP_Test_2_t(==, false)
    OP_Test_2_t(!=, true)
    OP_Test_2_t(>, true)
    OP_Test_2_t(<, false)
    OP_Test_2_t(>=, true)
    OP_Test_2_t(<=, false)
    // clang-format on
  }
}

SCENARIO("Unary Operator Test with class: " T_STRINGIFY(OO_TYPE), "[" TEST_PREFIX "unary_operator]") {
  GIVEN("An operand of type " T_STRINGIFY(OO_TYPE) " a") {
    OO_TYPE a = 10.0;

    REQUIRE(a.value() == 10.0);
    // clang-format off
    OP_Test_unary_t(++a, 11.0)
    OP_Test_unary_t(a++, 11.0)
    OP_Test_unary_t(--a, 9.0)
    OP_Test_unary_t(a--, 9.0)
    WHEN("-a") {
      OO_TYPE neg_a = -a;
      THEN("Value is negated") {
        REQUIRE(neg_a.value() == -10.0);
      }
    }
    // clang-format on
  }
}

#undef TEST_PREFIX
#undef OO_TYPE
