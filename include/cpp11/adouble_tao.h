/*
 * adouble_tao.h
 *
 *  Created on: Feb 22, 2016
 *      Author: ahueck
 */

// Using *https://github.com/taocpp/operators* to define operators.

#ifndef CPP11_ADOUBLE_TAO_H_
#define CPP11_ADOUBLE_TAO_H_

#include <iostream>
#include <cmath>

#define TAOCPP_NO_RVALUE_REFERENCE_RESULTS
#include <external/tao/operators.hpp>

#define ADOUBLE_SELF_OPERATORS_LIST \
  OP_SELF(+=) \
  OP_SELF(-=) \
  OP_SELF(*=) \
  OP_SELF(/=)

#define ADOUBLE_CMP_OPERATORS_LIST \
  OP_CMP(==) \
  OP_CMP(<)
  /* OP_CMP(>) manually defined for T > U */

class adouble
    : tao::operators::ordered_field<adouble>
    , tao::operators::ordered_field<adouble, double>
    , tao::operators::unit_steppable<adouble> {

private:
  double a;
public:
  adouble() noexcept : a(0.0) {

  }

  adouble(const double& v) noexcept : a( v ) {

  }

  adouble( const adouble& x ) noexcept : a( x.a ) {

  }

  adouble& operator=( const adouble& v ) noexcept {
    if(this != &v) {
      a = v.a;
    }
    return *this;
  }

  adouble& operator=( const double& v ) noexcept {
    a = v;
    return *this;
  }

  explicit operator double() const {
    return a;
  }

  inline double value() const {
    return a;
  }

  inline double& value() {
    return a;
  }

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

  adouble& operator++() {
    ++a;
    return *this;
  }

  adouble& operator--() {
    --a;
    return *this;
  }

  adouble& operator-() {
    a = -a;
    return *this;
  }
};

/*bool operator > (const adouble& lhs, const double& rhs) { \
  return lhs.value() > rhs;
}*/

#define OP_CMP(OP_) \
  bool operator OP_ (const adouble& lhs, const adouble& rhs) { \
    return lhs.value() OP_ rhs.value(); \
  } \
  bool operator OP_ (const adouble& lhs, const double& rhs) { \
    return lhs.value() OP_ rhs; \
  }
ADOUBLE_CMP_OPERATORS_LIST
#undef ADOUBLE_CMP_OPERATORS_LIST
#undef OP_CMP

std::istream& operator>> (std::istream& is, adouble& a) {
  double& val = a.value();
  is >> val;
  return is;
}

std::ostream& operator<< (std::ostream& os, const adouble& a) {
  os << a.value();
  return os;
}

#endif /* CPP11_ADOUBLE_TAO_H_ */
