/*
 * TestUtil.h
 *
 *  Created on: Nov 16, 2015
 *      Author: ahueck
 */

#ifndef TESTUTIL_H_
#define TESTUTIL_H_

#include <type_traits>
#include <iostream>

#define T_STRINGIFY_(A) # A
#define T_STRINGIFY__(A) T_STRINGIFY_(A)
#define T_STRINGIFY(A) T_STRINGIFY__(A)

namespace {
template <typename T>
auto v_impl(T&& t, std::false_type) -> decltype(t) {
  return t;
}
template <typename T>
auto v_impl(T&& t, std::true_type) -> typename std::remove_reference<decltype(t.value())>::type {
  auto val = t.value();
  return val;
}
template <typename T>
auto val(T&& t) -> decltype(v_impl(std::forward<T>(t), std::is_class<typename std::remove_reference<T>::type>())) {
  return v_impl(std::forward<T>(t), std::is_class<typename std::remove_reference<T>::type>());
}
}

#define _test_2_t(OP, EXPECTED) \
WHEN("a" T_STRINGIFY(OP) "b") { \
  const auto ad = val(a); \
  const auto bd = val(b); \
  auto c = a OP b; \
  THEN("a new value is created") { \
    auto cr = val(c); \
    if(std::is_same<bool, decltype(cr)>::value) \
	REQUIRE(EXPECTED == cr); \
    else \
	REQUIRE(EXPECTED == Approx(cr)); \
    AND_THEN("The old values are unchanged") { \
	REQUIRE(val(a) == ad); \
	REQUIRE(val(b) == bd); \
    } \
  } \
}

#define _test_1_t(OP, EXPECTED) \
WHEN("a" T_STRINGIFY(OP) "=b") { \
  const auto bd = val(b); \
  a OP##= b; \
  THEN("a is changed") { \
    REQUIRE(val(a) == Approx(EXPECTED)); \
    AND_THEN("b is unchanged") { \
	REQUIRE(val(b) == bd); \
    } \
  } \
}
#endif /* TESTUTIL_H_ */
