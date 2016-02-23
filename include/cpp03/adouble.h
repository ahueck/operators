// C++03 compatible operator overloading class *adouble*. Specifically making use of friend functionality.

#include <iostream>
#include <cmath>

#ifndef __adouble_H__
#define __adouble_H__

#define __NOOP_
#define __COMMA_ ,

#define __binary_template_decl_(ret_type, type, function) \
  ret_type function (const a##type& a, const a##type& b); \
  ret_type function (const type& a, const a##type& b); \
  ret_type function (const a##type& a, const type& b);

#define __friend_binary_template_def_(ret_type, type, function, inner, op) \
  friend ret_type function (const a##type& a, const a##type& b) { \
    return ret_type( inner(a.a op b.a) ); \
  } \
  friend ret_type function (const type& a, const a##type& b) { \
    return ret_type( inner(a op b.a) ); \
  } \
  friend ret_type function (const a##type& a, const type& b) { \
    return ret_type( inner(a.a op b) ); \
  }

#define __unary_template_decl_(type, function) \
    a##type function (const a##type& a); \

#define __friend_unary_template_def_(type, function, inner) \
  friend a##type function (const a##type& a) { \
    return a##type( inner(a.a) ); \
  }

#define __self_binary_template_def(type, op) \
  inline void operator op (const type& b) { \
    a op b; \
  } \
  inline void operator op (const a##type& b) { \
    a op b.a; \
  }

#define __increment_template_op_(type, op) \
  a##type& operator op () { \
    a op; \
    return *this; \
  } \
  a##type operator op (int) { \
    return a##type( op this->a ); \
  }

#define __trans_math_2_template_special_decl_(type, f) \
  a##type f (const int a, const a##type& b);

#define __trans_math_2_template_special_(type, f) \
  friend a##type f (const int a, const a##type& b) { \
    return a##type( f(a, b.a) ); \
  }

// adouble specifics:
#define __friend_binary_op_decl_(op) \
  __binary_template_decl_(adouble, double, operator op)
#define __friend_binary_op_(op) \
  __friend_binary_template_def_(adouble, double, operator op, __NOOP_, op)

#define __friend_binary_cmp_op_decl_(op) \
  __binary_template_decl_(bool, double, operator op)
#define __friend_binary_cmp_op_(op) \
  __friend_binary_template_def_(bool, double, operator op, __NOOP_, op)

#define __self_binary_op_(op) \
  __self_binary_template_def(double, op)

#define __increment_op_(op) \
  __increment_template_op_(double, op)

#define __friend_unary_op_decl_(op) \
  __unary_template_decl_(double, operator op)
#define __friend_unary_op_(op) \
  __friend_unary_template_def_(double, operator op, op)

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

__friend_binary_op_decl_(+)
__friend_binary_op_decl_(-)
__friend_binary_op_decl_(*)
__friend_binary_op_decl_(/)
__friend_binary_cmp_op_decl_(<)
__friend_binary_cmp_op_decl_(>)
__friend_binary_cmp_op_decl_(<=)
__friend_binary_cmp_op_decl_(>=)
__friend_binary_cmp_op_decl_(==)
__friend_binary_cmp_op_decl_(!=)

__friend_unary_op_decl_(-)

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
  __friend_binary_cmp_op_(<)
  __friend_binary_cmp_op_(>)
  __friend_binary_cmp_op_(<=)
  __friend_binary_cmp_op_(>=)
  __friend_binary_cmp_op_(==)
  __friend_binary_cmp_op_(!=)

  __friend_unary_op_(-)

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
  __trans_math_(y0)
  __trans_math_(y1)

  __trans_math_2_special_(yn)
  __trans_math_2_special_(jn)

  __trans_math_2_(pow)
  __trans_math_2_(hypot)
  __trans_math_2_(atan2)
  __trans_math_2_std_(min)
  __trans_math_2_std_(max)

  friend std::istream& operator>> (std::istream& is, adouble& a) {
    is >> a.a;
    return is;
  }

  friend std::ostream& operator<< (std::ostream& os, const adouble& a) {
    os << a.a;
    return os;
  }
};

#endif // __adouble_H__
