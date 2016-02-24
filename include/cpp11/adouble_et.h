/*
 * adouble.h
 *
 *  Created on: Feb 22, 2016
 *      Author: ahueck
 */

#ifndef __adouble_et_H__
#define __adouble_et_H__

#include <iostream>
#include <type_traits>
#include <cmath>

#include "binary_op.hpp"
#include "unary_op.hpp"

namespace operators {
namespace et {

template<typename T>
class TypeTraits {
public:
  typedef typename std::remove_reference<T>::type type;
  typedef type& ref_type;
  typedef type const &cref_type;
};

template<typename DType, typename T>
class Expression {
  //typedef typename TypeTraits<DType>::type real;

  Expression& operator=(const Expression&) = delete;

public:
  const T& cast() const {
    return static_cast<const T&>(*this);
  }

  auto value() const -> typename TypeTraits<DType>::type {
    return cast().value();
  }
};

__binary_op(Add, +)
__binary_op(Mul, *)
__binary_op(Sub, -)
__binary_op(Div, /)

__binary_op_cmpl(==)
__binary_op_cmpl(!=)
__binary_op_cmpl(<)
__binary_op_cmpl(>)
__binary_op_cmpl(>=)
__binary_op_cmpl(<=)

__trans_math(Fabs, fabs)
__trans_math_std(Abs, abs)
__trans_math(Round, round)
__trans_math(Ceil, ceil)
__trans_math(Floor, floor)
// cf. https://www.gnu.org/software/libc/manual/html_node/Exponents-and-Logarithms.html
__trans_math(Exp, exp)
__trans_math(Exp2, exp2)
__trans_math(Exp10, exp10)
__trans_math(Log, log)
__trans_math(Log10, log10)
__trans_math(Log2, log2)
__trans_math(Logb, logb)
__trans_math(Sqrt, sqrt)
__trans_math(Cbrt, cbrt)
__trans_math(Expm1, expm1)
__trans_math(Log1p, log1p)
// cf. https://www.gnu.org/software/libc/manual/html_node/Trig-Functions.html
__trans_math(Sin, sin)
__trans_math(Cos, cos)
__trans_math(Tan, tan)
__trans_math(Sincos, sincos)
// cf. https://www.gnu.org/software/libc/manual/html_node/Inverse-Trig-Functions.html
__trans_math(Asin, asin)
__trans_math(Acos, acos)
__trans_math(Atan, atan)
// cf. https://www.gnu.org/software/libc/manual/html_node/Hyperbolic-Functions.htm
__trans_math(Sinh, sinh)
__trans_math(Cosh, cosh)
__trans_math(Tanh, tanh)
__trans_math(Asinh, asinh)
__trans_math(Acosh, acosh)
__trans_math(Atanh, atanh)
// cf. https://www.gnu.org/software/libc/manual/html_node/Special-Functions.html
__trans_math(Erf, erf)
__trans_math(Erfc, erfc)
__trans_math(Lgamma, lgamma)
// Missing: "lgamma_r (double x, int *signp)"
__trans_math(Gamma, gamma)
__trans_math(J0, j0)
__trans_math(J1, j1)
__trans_math(Y0, y0)
__trans_math(Y1, y1)

__trans_math_2(Pow, pow)
__trans_math_2(Hypot, hypot)
__trans_math_2(Atan2, atan2)
__trans_math_2_std(Min, min)
__trans_math_2_std(Max, max)

template<typename Dtype>
class number : public Expression<Dtype, number<Dtype>> {
  //typedef typename TypeTraits<Dtype>::type real;

public:
  number() : data() {
  }

  number(typename TypeTraits<Dtype>::cref_type a) : data(a) {
  }

  template<typename T>
  number(const Expression<Dtype, T>& a) : data(a.value()) {
  }

  number(const number<Dtype>& a) : data(a.data) {
  }

  auto value() const -> typename TypeTraits<Dtype>::type {
    return data;
  }

  auto operator=(typename TypeTraits<Dtype>::cref_type a) -> typename std::add_lvalue_reference<decltype(*this)>::type {
    data = a;
    return *this;
  }

  template<typename T>
  auto operator=(const Expression<Dtype, T>& a) -> typename std::add_lvalue_reference<decltype(*this)>::type {
    if(this != &a) {
      data = a.value();
    }
    return *this;
  }

  auto operator=(const number<Dtype>& a) -> typename std::add_lvalue_reference<decltype(*this)>::type {
    if(this != &a) {
      data = a.value;
    }
    return *this;
  }

  template<class T>
  auto operator+=(const Expression<Dtype, T>& a) -> typename std::add_lvalue_reference<decltype(*this)>::type {
    return *this = (*this + a);
  }

private:
  Dtype data;
};

template<typename Dtype, class T>
std::ostream& operator<<(std::ostream& os, const Expression<Dtype, T>& a){
  os << a.value();
  return os;
}

typedef number<double> adouble;

}
}

#undef BIN_OP
#undef BIN_OP_L
#undef BIN_OP_R
#undef __noop
#undef __comma
#undef __binary_op_cmpl
#undef __trans_math_2
#undef __trans_math_2_std
#undef __binary_op

#undef UN_OP
#undef __trans_math
#undef __trans_math_std
#undef __unary_op

#endif /* __adouble_et_H__ */
