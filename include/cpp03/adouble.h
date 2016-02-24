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

#include <util/macro_oo.h>

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

  __oo_self_binary_op(+=)
  __oo_self_binary_op(-=)
  __oo_self_binary_op(*=)
  __oo_self_binary_op(/=)

  __oo_unitstep_op(++)
  __oo_unitstep_op(--)

  friend std::istream& operator>> (std::istream& is, adouble& a) {
    is >> a.a;
    return is;
  }

  friend std::ostream& operator<< (std::ostream& os, const adouble& a) {
    os << a.a;
    return os;
  }
};


__oo_binary_op(+)
__oo_binary_op(-)
__oo_binary_op(*)
__oo_binary_op(/)
__oo_binary_cmp_op(<)
__oo_binary_cmp_op(>)
__oo_binary_cmp_op(<=)
__oo_binary_cmp_op(>=)
__oo_binary_cmp_op(==)
__oo_binary_cmp_op(!=)

__oo_unary_op(-)

__oo_math(fabs)
__oo_math_std(abs)
__oo_math(round)
__oo_math(ceil)
__oo_math(floor)
// cf. https://www.gnu.org/software/libc/manual/html_node/Exponents-and-Logarithms.html
__oo_math(exp)
__oo_math(exp2)
__oo_math(exp10)
__oo_math(log)
__oo_math(log10)
__oo_math(log2)
__oo_math(logb)
__oo_math(sqrt)
__oo_math(cbrt)
__oo_math(expm1)
__oo_math(log1p)
// cf. https://www.gnu.org/software/libc/manual/html_node/Trig-Functions.html
__oo_math(sin)
__oo_math(cos)
__oo_math(tan)
//  __oo_math(sincos)
// cf. https://www.gnu.org/software/libc/manual/html_node/Inverse-Trig-Functions.html
__oo_math(asin)
__oo_math(acos)
__oo_math(atan)
// cf. https://www.gnu.org/software/libc/manual/html_node/Hyperbolic-Functions.htm
__oo_math(sinh)
__oo_math(cosh)
__oo_math(tanh)
__oo_math(asinh)
__oo_math(acosh)
__oo_math(atanh)
// cf. https://www.gnu.org/software/libc/manual/html_node/Special-Functions.html
__oo_math(erf)
__oo_math(erfc)
__oo_math(lgamma)
// Missing: "lgamma_r (double x, int *signp)"
__oo_math(gamma)
__oo_math(j0)
__oo_math(j1)
__oo_math(y0)
__oo_math(y1)

__oo_math_2_special(yn)
__oo_math_2_special(jn)

__oo_math_2(pow)
__oo_math_2(hypot)
__oo_math_2(atan2)
__oo_math_2_std(min)
__oo_math_2_std(max)

std::istream& operator>> (std::istream& is, adouble& a);
std::ostream& operator<< (std::ostream& os, const adouble& a);

#endif /* ADOUBLE_H_ */
