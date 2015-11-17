/*
 * TestUtil.h
 *
 *  Created on: Nov 16, 2015
 *      Author: ahueck
 */

#ifndef TESTUTIL_H_
#define TESTUTIL_H_

#include <type_traits>

#define T_STRINGIFY_(A) # A
#define T_STRINGIFY__(A) T_STRINGIFY_(A)
#define T_STRINGIFY(A) T_STRINGIFY__(A)

namespace {
template<typename U>
inline auto val(U&& val) -> decltype(val.value()) {
  return val.value();
}

inline bool val(bool val) {
  return val;
}
}

#define _test_2_t(OP, EXPECTED) \
WHEN("a" T_STRINGIFY(OP) "b") { \
  const auto ad = a.value(); \
  const auto bd = b.value(); \
  auto c = a OP b; \
  THEN("a new value is created") { \
    auto cr = val(c); \
    if(std::is_same<bool, decltype(cr)>::value) \
	REQUIRE(EXPECTED == cr); \
    else \
	REQUIRE(EXPECTED == Approx(cr)); \
    AND_THEN("The old values are unchanged") { \
	REQUIRE(a.value() == ad); \
	REQUIRE(b.value() == bd); \
    } \
  } \
}

#define _test_1_t(OP, EXPECTED) \
WHEN("a" T_STRINGIFY(OP) "=b") { \
  const auto bd = b.value(); \
  a OP##= b; \
  THEN("a is changed") { \
    REQUIRE(a.value() == Approx(EXPECTED)); \
    AND_THEN("b is unchanged") { \
	REQUIRE(b.value() == bd); \
    } \
  } \
}
#endif /* TESTUTIL_H_ */
