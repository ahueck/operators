/*
 * adouble.h
 *
 *  Created on: Feb 24, 2016
 *      Author: ahueck
 */

#include <iostream>
#include <cmath>

#ifndef ADOUBLE_H_
#define ADOUBLE_H_

#define ADOUBLE_SELF_OPERATORS_LIST \
  OP_SELF(+=) \
  OP_SELF(-=) \
  OP_SELF(*=) \
  OP_SELF(/=) \

#define ADOUBLE_CMP_OPERATORS_LIST \
  OP_CMP(==) \
  OP_CMP(!=) \
  OP_CMP(>=) \
  OP_CMP(<=) \
  OP_CMP(<) \
  OP_CMP(>)

#define ADOUBLE_UNITSTEP_OPERATORS_LIST \
  OP_UNITSTEP(++) \
  OP_UNITSTEP(--)

#define ADOUBLE_ARITHMETIC_OPERATORS_LIST \
  OP_ARITHMETIC(+) \
  OP_ARITHMETIC(-) \
  OP_ARITHMETIC(*) \
  OP_ARITHMETIC(/)

#define ADOUBLE_UNARY_OPERATORS_LIST \
  OP_UNARY(-)

#define ADOUBLE_UNARY_MATH_LIST \
  OP_MATH_UN(round) \
  OP_MATH_UN(ceil) \
  OP_MATH_UN(floor) \
  OP_MATH_UN(fabs) \
  /* for compatibility: */ \
  OP_MATH_UN(abs) \
  /* cf. https://www.gnu.org/software/libc/manual/html_node/Exponents-and-Logarithms.html */ \
  OP_MATH_UN(exp) \
  OP_MATH_UN(exp2) \
  OP_MATH_UN(exp10) \
  OP_MATH_UN(log) \
  OP_MATH_UN(log10) \
  OP_MATH_UN(log2) \
  OP_MATH_UN(logb) \
  OP_MATH_UN(sqrt) \
  OP_MATH_UN(cbrt) \
  OP_MATH_UN(expm1) \
  OP_MATH_UN(log1p) \
  /* cf. https://www.gnu.org/software/libc/manual/html_node/Trig-Functions.html */ \
  OP_MATH_UN(sin) \
  OP_MATH_UN(cos) \
  OP_MATH_UN(tan) \
  /* OP_MATH_UN(sincos) */ \
  /* cf. https://www.gnu.org/software/libc/manual/html_node/Inverse-Trig-Functions.html */ \
  OP_MATH_UN(asin) \
  OP_MATH_UN(acos) \
  OP_MATH_UN(atan) \
  /* cf. https://www.gnu.org/software/libc/manual/html_node/Hyperbolic-Functions.htm */ \
  OP_MATH_UN(sinh) \
  OP_MATH_UN(cosh) \
  OP_MATH_UN(tanh) \
  OP_MATH_UN(asinh) \
  OP_MATH_UN(acosh) \
  OP_MATH_UN(atanh) \
  /* cf. https://www.gnu.org/software/libc/manual/html_node/Special-Functions.html */ \
  OP_MATH_UN(erf) \
  OP_MATH_UN(erfc) \
  OP_MATH_UN(lgamma) \
  /* Missing: "lgamma_r (double x, int *signp)" */ \
  OP_MATH_UN(gamma) \
  OP_MATH_UN(j0) \
  OP_MATH_UN(j1) \
  OP_MATH_UN(y0) \
  OP_MATH_UN(y1)

#define ADOUBLE_BINARY_MATH_LIST \
  OP_MATH_BIN(pow) \
  OP_MATH_BIN(hypot) \
  OP_MATH_BIN(atan2) \
  OP_MATH_BIN(fmin) \
  OP_MATH_BIN(fmax) \
  OP_MATH_BIN(min, std::) \
  OP_MATH_BIN(max, std::)

class adouble {
private:
  double a;
public:
  adouble() : a(0.0) {

  }
  adouble(double other) : a(other) {

  }
  adouble(const adouble& other) : a(other.a) {

  }

  inline double value() const {
    return a;
  }

  inline double& value() {
    return a;
  }

  inline double getValue() const {
    return a;
  }

  inline double& getValue() {
    return a;
  }

  inline adouble& operator=(const double& other) {
    a = other;
    return *this;
  }

  inline adouble& operator=(const adouble& other) {
    if(this != &other) {
      a = other.a;
    }
    return *this;
  }

#define OP_UNARY(OP_) \
  adouble& operator OP_ () { \
    a = OP_ a; \
    return *this; \
  }
ADOUBLE_UNARY_OPERATORS_LIST
#undef ADOUBLE_UNARY_OPERATORS_LIST
#undef OP_UNARY

#define OP_UNITSTEP(OP_) \
  adouble& operator OP_ () { \
    OP_ a; \
    return *this; \
  } \
  adouble operator OP_ (int) { \
    adouble res(a); \
    OP_ a; \
    return res; \
  }
ADOUBLE_UNITSTEP_OPERATORS_LIST
#undef ADOUBLE_UNITSTEP_OPERATORS_LIST
#undef OP_UNITSTEP

#define OP_SELF(OP_) \
  adouble& operator OP_ (const adouble& other) { \
    a OP_ other.a; \
    return *this; \
  } \
  adouble& operator OP_ (const double& other) { \
    a OP_ other; \
    return *this; \
  }
ADOUBLE_SELF_OPERATORS_LIST
#undef ADOUBLE_SELF_OPERATORS_LIST
#undef OP_SELF
};

#define OP_CMP(OP_) \
  bool operator OP_ (const adouble& lhs, const adouble& rhs) { \
    return lhs.value() OP_ rhs.value(); \
  } \
  bool operator OP_ (const adouble& lhs, const double& rhs) { \
    return lhs.value() OP_ rhs; \
  } \
  bool operator OP_ (const double& lhs, const adouble& rhs) { \
    return lhs OP_ rhs.value(); \
  }
ADOUBLE_CMP_OPERATORS_LIST
#undef ADOUBLE_CMP_OPERATORS_LIST
#undef OP_CMP

#define OP_ARITHMETIC(OP_) \
  adouble operator OP_ (const adouble& lhs, const adouble& rhs) { \
	return adouble(lhs.value() OP_ rhs.value()); \
  } \
  adouble operator OP_ (const adouble& lhs, const double& rhs) { \
	  return adouble(lhs.value() OP_ rhs); \
  } \
  adouble operator OP_ (const double& lhs, const adouble& rhs) { \
	  return adouble(lhs OP_ rhs.value()); \
  }
ADOUBLE_ARITHMETIC_OPERATORS_LIST
#undef ADOUBLE_ARITHMETIC_OPERATORS_LIST
#undef OP_ARITHMETIC

#define OP_MATH_UN(F_) \
  adouble F_ (const adouble& arg) { \
    return adouble(F_(arg.value())); \
  }
ADOUBLE_UNARY_MATH_LIST
#undef ADOUBLE_UNARY_MATH_LIST
#undef OP_MATH_UN

// FIXME generates warning because of unused VA_ARGS (when no std:: passed)
//#define GET_F_NAME(ELEMENT1, ...) ELEMENT1
#define OP_MATH_BIN(F_, ...) \
  adouble F_ (const adouble& lhs, const adouble& rhs) { \
    return adouble(__VA_ARGS__ F_(lhs.value(), rhs.value())); \
  } \
  adouble F_ (const adouble& lhs, const double& rhs) { \
      return adouble(__VA_ARGS__ F_(lhs.value(), rhs)); \
  } \
  adouble F_ (const double& lhs, const adouble& rhs) { \
      return adouble(__VA_ARGS__ F_(lhs, rhs.value())); \
  }
ADOUBLE_BINARY_MATH_LIST
#undef ADOUBLE_BINARY_MATH_LIST
#undef OP_MATH_BIN

std::istream& operator>> (std::istream& is, adouble& arg) {
  double& val = arg.value();
  is >> val;
  return is;
}

std::ostream& operator<< (std::ostream& os, const adouble& arg) {
  os << arg.value();
  return os;
}

#endif /* ADOUBLE_H_ */
