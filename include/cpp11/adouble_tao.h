// C++11 compatible operator overloading class *adouble*. Using *https://github.com/taocpp/operators* to define operators.

#ifndef ADOUBLE_TAO_H_
#define ADOUBLE_TAO_H_

#include <iostream>
#include <cmath>

#define TAOCPP_NO_RVALUE_REFERENCE_RESULTS
#include <external/tao/operators.hpp>

#include <util/macro_oo.h>

#define __trans_math_decl_(f) \
  __unary_template_decl_(double, f)
#define __trans_math_(f) \
  __friend_unary_template_def_(double, f, f)
#define __trans_math_std_(f) \
  __friend_unary_template_def_(double, f, std::f)

#define __trans_math_decl_2_(f) \
  __binary_template_decl_(adouble, double, f)
#define __trans_math_2_(f) \
  __friend_binary_template_def_(adouble, double, f, f, __COMMA_)
#define __trans_math_2_std_(f) \
  __friend_binary_template_def_(adouble, double, f, std::f, __COMMA_)

#define __trans_math_2_special_decl_(f) \
  __trans_math_2_template_special_decl_(double, f)
#define __trans_math_2_special_(f) \
  __trans_math_2_template_special_(double, f)

class adouble;

bool operator==(const adouble& lhs, const adouble& rhs);
bool operator<(const adouble& lhs, const adouble& rhs);
bool operator==(const adouble& x, const double& v);
bool operator<(const adouble& x, const double& v);
bool operator>(const adouble& x, const double& v);

__trans_math_decl_(round)
__trans_math_decl_(ceil)
__trans_math_decl_(floor)
__trans_math_decl_(fabs)
// for compatibility:
__trans_math_decl_(abs)
// cf. https://www.gnu.org/software/libc/manual/html_node/Exponents-and-Logarithms.html
__trans_math_decl_(exp)
__trans_math_decl_(exp2)
__trans_math_decl_(exp10)
__trans_math_decl_(log)
__trans_math_decl_(log10)
__trans_math_decl_(log2)
__trans_math_decl_(logb)
__trans_math_decl_(sqrt)
__trans_math_decl_(cbrt)
__trans_math_decl_(expm1)
__trans_math_decl_(log1p)
// cf. https://www.gnu.org/software/libc/manual/html_node/Trig-Functions.html
__trans_math_decl_(sin)
__trans_math_decl_(cos)
__trans_math_decl_(tan)
//__trans_math_decl_(sincos)
// cf. https://www.gnu.org/software/libc/manual/html_node/Inverse-Trig-Functions.html
__trans_math_decl_(asin)
__trans_math_decl_(acos)
__trans_math_decl_(atan)
// cf. https://www.gnu.org/software/libc/manual/html_node/Hyperbolic-Functions.htm
__trans_math_decl_(sinh)
__trans_math_decl_(cosh)
__trans_math_decl_(tanh)
__trans_math_decl_(asinh)
__trans_math_decl_(acosh)
__trans_math_decl_(atanh)
// cf. https://www.gnu.org/software/libc/manual/html_node/Special-Functions.html
__trans_math_decl_(erf)
__trans_math_decl_(erfc)
__trans_math_decl_(lgamma)
// Missing: "lgamma_r (double x, int *signp)"
__trans_math_decl_(gamma)
__trans_math_decl_(j0)
__trans_math_decl_(j1)
__trans_math_decl_(y0)
__trans_math_decl_(y1)
__trans_math_2_special_decl_(yn)
__trans_math_2_special_decl_(jn)

__trans_math_decl_2_(pow)
__trans_math_decl_2_(hypot)
__trans_math_decl_2_(atan2)
__trans_math_decl_2_(min)
__trans_math_decl_2_(max)

std::istream& operator>> (std::istream& is, adouble& a);
std::ostream& operator<< (std::ostream& os, const adouble& a);


class adouble
    : tao::operators::ordered_field<adouble>
    , tao::operators::ordered_field<adouble, double>
    , tao::operators::unit_steppable<adouble> {
public:
  adouble() noexcept : a() {

  }

  explicit adouble(const double& v) noexcept : a( v ) {

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

  adouble& operator+=( const adouble& x ) noexcept {
    a += x.a;
    return *this;
  }
  adouble& operator-=( const adouble& x ) {
    a -= x.a;
    return *this;
  }
  adouble& operator*=( const adouble& x ) {
    a *= x.a;
    return *this;
  }
  adouble& operator/=( const adouble& x ) {
    a /= x.a;
    return *this;
  }

  adouble& operator+=( const double& v ) {
    a += v;
    return *this;}
  adouble& operator-=( const double& v ) {
    a -= v;
    return *this;}
  adouble& operator*=( const double& v ) {
    a *= v;
    return *this;}
  adouble& operator/=( const double& v ) {
    a /= v;
    return *this;}

  adouble& operator++() {
    ++a;
    return *this;
  }

  adouble& operator--() {
    --a;
    return *this;
  }

  friend bool operator==(const adouble& lhs, const adouble& rhs) {
    return lhs.a == rhs.a;
  }

  friend bool operator<(const adouble& lhs, const adouble& rhs) {
    return lhs.a < rhs.a;
  }

  friend bool operator==(const adouble& x, const double& v) {
    return x.a == v;
  }

  friend bool operator<(const adouble& x, const double& v) {
    return x.a < v;
  }

  friend bool operator>(const adouble& x, const double& v) {
    return x.a > v;
  }

  friend std::istream& operator>> (std::istream& is, adouble& a) {
    is >> a.a;
    return is;
  }

  friend std::ostream& operator<< (std::ostream& os, const adouble& a) {
    os << a.a;
    return os;
  }


  __trans_math_(fabs)
  __trans_math_std_(abs)
  __trans_math_(round)
  __trans_math_(ceil)
  __trans_math_(floor)
  // cf. https://www.gnu.org/software/libc/manual/html_node/Exponents-and-Logarithms.html
  __trans_math_(exp)
  __trans_math_(exp2)
  __trans_math_(exp10)
  __trans_math_(log)
  __trans_math_(log10)
  __trans_math_(log2)
  __trans_math_(logb)
  __trans_math_(sqrt)
  __trans_math_(cbrt)
  __trans_math_(expm1)
  __trans_math_(log1p)
  // cf. https://www.gnu.org/software/libc/manual/html_node/Trig-Functions.html
  __trans_math_(sin)
  __trans_math_(cos)
  __trans_math_(tan)
//  __trans_math_(sincos)
  // cf. https://www.gnu.org/software/libc/manual/html_node/Inverse-Trig-Functions.html
  __trans_math_(asin)
  __trans_math_(acos)
  __trans_math_(atan)
  // cf. https://www.gnu.org/software/libc/manual/html_node/Hyperbolic-Functions.htm
  __trans_math_(sinh)
  __trans_math_(cosh)
  __trans_math_(tanh)
  __trans_math_(asinh)
  __trans_math_(acosh)
  __trans_math_(atanh)
  // cf. https://www.gnu.org/software/libc/manual/html_node/Special-Functions.html
  __trans_math_(erf)
  __trans_math_(erfc)
  __trans_math_(lgamma)
  // Missing: "lgamma_r (double x, int *signp)"
  __trans_math_(gamma)
  __trans_math_(j0)
  __trans_math_(j1)
  __trans_math_(y0)
  __trans_math_(y1)

  __trans_math_2_special_(yn)
  __trans_math_2_special_(jn)

  __trans_math_2_(pow)
  __trans_math_2_(hypot)
  __trans_math_2_(atan2)
  __trans_math_2_std_(min)
  __trans_math_2_std_(max)

private:
  double a;
};

#endif /* ADOUBLE_TAO_H_ */
