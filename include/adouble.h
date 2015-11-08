#include <iostream>
#include <cmath>

#ifndef __adouble_H__
#define __adouble_H__

using namespace std;

#define __friend_unary_op_decl_(op) \
  adouble operator op (const adouble& a);

#define __friend_unary_op_(op) \
  friend adouble operator op (const adouble& a) { \
    return adouble( op a.a ); \
  }

#define __friend_binary_op_decl_(op) \
  adouble operator op (const adouble& a, const adouble& b); \
  adouble operator op (const double& a, const adouble& b); \
  adouble operator op (const adouble& a, const double& b);

#define __friend_binary_op_(op) \
  friend adouble operator op (const adouble& a, const adouble& b) { \
    return adouble(a.a op b.a); \
  } \
  friend adouble operator op (const double& a, const adouble& b) { \
    return adouble(a op b.a); \
  } \
  friend adouble operator op (const adouble& a, const double& b) { \
    return adouble(a.a op b); \
  }

#define __self_binary_op_(op) \
  inline void operator op (const double& other) { \
    a op other; \
  } \
  inline void operator op (const adouble& other) { \
    a op other.a; \
  }

#define __increment_op_(op) \
  adouble& operator op () { \
    a op ; \
    return *this; \
  } \
  adouble operator op (int) { \
    return adouble(op this->a); \
  }

#define __trans_math_decl_(f) \
  adouble f (const adouble& a);

#define __trans_math_(f) \
  friend adouble f (const adouble& a) { \
    return adouble( f (a.a) ); \
  }

#define __trans_math_decl_2_(f) \
  adouble f (const adouble& a, const adouble& b); \
  adouble f (const double& a, const adouble& b); \
  adouble f (const adouble& a, const double& b);

#define __trans_math_2_(f) \
  friend adouble f (const adouble& a, const adouble& b) { \
    return adouble( f (a.a, b.a) ); \
  } \
  friend adouble f (const double& a, const adouble& b) { \
    return adouble( f (a, b.a) ); \
  } \
  friend adouble f (const adouble& a, const double& b) { \
    return adouble( f (a.a, b) ); \
  }

class adouble;

__friend_binary_op_decl_(+)
__friend_binary_op_decl_(-)
__friend_binary_op_decl_(*)
__friend_binary_op_decl_(/)
__friend_binary_op_decl_(<)
__friend_binary_op_decl_(>)
__friend_binary_op_decl_(<=)
__friend_binary_op_decl_(>=)
__friend_binary_op_decl_(==)

__friend_unary_op_decl_(-)

__trans_math_decl_(fabs)
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
__trans_math_decl_(sincos)
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
__trans_math_decl_(jn)
__trans_math_decl_(y0)
__trans_math_decl_(y1)
__trans_math_decl_(yn)

__trans_math_decl_2_(pow)
__trans_math_decl_2_(hypot)
__trans_math_decl_2_(atan2)
__trans_math_decl_2_(min)
__trans_math_decl_2_(max)

istream& operator>> (istream& is, adouble& a);
ostream& operator<< (ostream& os, const adouble& a);


class adouble {
private:
  double a;
public:
  static const adouble zero;
  static const adouble one;

  adouble() : a(0.0) {

  }
  adouble(double other) : a(other) {

  }
  adouble(const adouble& other) : a(other.a) {

  }

  inline const double& value() const {
    return a;
  }

  inline double& value() {
    return a;
  }

  inline const double& getValue() const {
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
    if(&other != this) {
      a = other.a;
    }
    return *this;
  }

  __self_binary_op_(+=)
  __self_binary_op_(-=)
  __self_binary_op_(*=)
  __self_binary_op_(/=)

  __increment_op_(++)
  __increment_op_(--)

// Friend operators
  __friend_binary_op_(+)
  __friend_binary_op_(-)
  __friend_binary_op_(*)
  __friend_binary_op_(/)
  __friend_binary_op_(<)
  __friend_binary_op_(>)
  __friend_binary_op_(<=)
  __friend_binary_op_(>=)
  __friend_binary_op_(==)

  __friend_unary_op_(-)

  __trans_math_(fabs)
  __trans_math_(abs)
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
  __trans_math_(sincos)
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
  __trans_math_(jn)
  __trans_math_(y0)
  __trans_math_(y1)
  __trans_math_(yn)

  __trans_math_2_(pow)
  __trans_math_2_(hypot)
  __trans_math_2_(atan2)
  __trans_math_2_(min)
  __trans_math_2_(max)

  friend istream& operator>> (istream& is, adouble& a) {
    is >> a.a;
  }

  friend ostream& operator<< (ostream& os, const adouble& a) {
    os << a.a;
  }
};

const adouble adouble::zero = adouble(0.0);
const adouble adouble::one = adouble(1.0);

#endif // __adouble_H__
