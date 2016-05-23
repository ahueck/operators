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

#define ADOUBLE_CMP_OPERATORS_LIST \
  OP_CMP(==) \
  OP_CMP(!=) \
  OP_CMP(>=) \
  OP_CMP(<=) \
  OP_CMP(<) \
  OP_CMP(>)

#define ADOUBLE_ARITHMETIC_OPERATORS_LIST \
  OP_ARITHMETIC(Add, +) \
  OP_ARITHMETIC(Mul, -) \
  OP_ARITHMETIC(Sub, *) \
  OP_ARITHMETIC(Div, /)

#define ADOUBLE_UNITSTEP_OPERATORS_LIST \
  OP_UNITSTEP(++) \
  OP_UNITSTEP(--)

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


template<typename T>
class TypeTraits {
public:
  typedef typename std::remove_reference<T>::type type;
  typedef type& ref_type;
  typedef type const &cref_type;
};

template<typename Dtype, typename T>
class Expression {
  //typedef typename TypeTraits<DType>::type real;

  Expression& operator=(const Expression&) = delete;

public:
  const T& cast() const {
    return static_cast<const T&>(*this);
  }

  auto value() const -> Dtype {
    return cast().value();
  }
};

template<typename Dtype>
class scalar : public Expression<Dtype, scalar<Dtype>> {
private:
  Dtype data;

public:
  scalar() : data() {
  }

  scalar(typename TypeTraits<Dtype>::cref_type a) : data(a) {
  }

  template<typename T>
  scalar(const Expression<Dtype, T>& a) : data(a.data) {
  }

  scalar(const scalar<Dtype>& a) : data(a.data) {
  }

  auto value() const -> Dtype {
    return data;
  }

  auto operator=(typename TypeTraits<Dtype>::cref_type a) -> scalar<Dtype>& {
    data = a;
    return *this;
  }

  template<typename T>
  auto operator=(const Expression<Dtype, T>& a) -> scalar<Dtype>& {
    if(this != &a) {
      data = a.value();
    }

    return *this;
  }

  auto operator=(const scalar<Dtype>& a) -> scalar<Dtype>& {
    if(this != &a) {
      data = a.value;
    }

    return *this;
  }

  template<class T>
  auto operator+=(const Expression<Dtype, T>& a) -> scalar<Dtype>& {
    return *this = (*this + a);
  }

#define OP_UNARY(OP_) \
  auto operator OP_ () -> scalar<Dtype>& { \
    a = OP_ a; \
    return *this; \
  }
ADOUBLE_UNARY_OPERATORS_LIST
#undef ADOUBLE_UNARY_OPERATORS_LIST
#undef OP_UNARY

#define OP_UNITSTEP(OP_) \
  auto operator OP_ () -> scalar<Dtype>& { \
    OP_ a; \
    return *this; \
  } \
  auto operator OP_ (int) -> scalar<Dtype>& { \
    adouble res(a); \
    OP_ a; \
    return res; \
  }
ADOUBLE_UNITSTEP_OPERATORS_LIST
#undef ADOUBLE_UNITSTEP_OPERATORS_LIST
#undef OP_UNITSTEP

};

template<typename Dtype, class T>
std::ostream& operator<<(std::ostream& os, const Expression<Dtype, T>& a){
  os << a.value();
  return os;
}

#define OP_CMP(OP_) \
  template <typename Dtype, typename T> \
  inline auto operator OP_(const Expression<Dtype, T>& a, const Dtype& b) -> decltype(a.value() OP_ b) { \
    return a.value() OP_ b; \
  } \
  template <typename Dtype, typename U> \
  inline auto operator OP_(const Dtype& a, const Expression<Dtype, U>& b) -> decltype(a OP_ b.value()) { \
    return a OP_ b.value(); \
  } \
  template <typename Dtype, typename T, typename U> \
  inline auto operator OP_(const Expression<Dtype, T>& a, const Expression<Dtype, U>& b) -> decltype(a.value() OP_ b.value()) { \
    return a.value() OP_ b.value(); \
  }
ADOUBLE_CMP_OPERATORS_LIST
#undef ADOUBLE_CMP_OPERATORS_LIST

#define OP_ARITHMETIC(name, op) \
template<typename Dtype, typename T, typename U> \
class name##Expr: public Expression<Dtype, name##Expr<Dtype, T, U>> { \
private: \
  const T& t; \
  const U& u; \
public: \
  explicit name##Expr(const Expression<Dtype, T>& a, const Expression<Dtype, U>& b) \
    : t(a.cast()) \
    , u(b.cast()) \
  { \
  } \
  auto value() const -> decltype(t.value() op u.value()) { \
    return t.value() op u.value();  \
  } \
};\
template<typename Dtype, typename T> \
class name##LeftExpr: public Expression<Dtype, name##LeftExpr<Dtype, T>> { \
private: \
  const T& t; \
  const Dtype u; \
public: \
  explicit name##LeftExpr(const Expression<Dtype, T>& a, const Dtype& b) \
    : t(a.cast()) \
    , u(b) \
  { \
  } \
  auto value() const -> decltype(t.value() op u) { \
    return t.value() op u; \
  } \
}; \
template<typename Dtype, typename U> \
class name##RightExpr: public Expression<Dtype, name##RightExpr<Dtype, U>> { \
private: \
  const Dtype t; \
  const U& u; \
public: \
  explicit name##RightExpr(const Dtype& a, const Expression<Dtype, T>& b) \
    : t(a) \
    , u(b.cast()) \
  { \
  } \
  auto value() const -> decltype(t op u.value()) { \
    return t op u.value(); \
  } \
}; \
	\
template <typename Dtype, typename T, typename U> \
inline auto operator op(const Expression<Dtype, T>& a, const Expression<Dtype, U>& b) -> decltype(name##Expr<Dtype, T, U>(a.cast(), b.cast())) { \
  return name##Expr<Dtype, T, U>(a.cast(), b.cast()); \
} \
template <typename Dtype, typename T> \
inline auto operator op(const Expression<Dtype, T>& a, const Dtype& b) -> decltype(name##LeftExpr<Dtype, T>(a.cast(), b)) { \
  return name##LeftExpr<Dtype, T>(a.cast(), b); \
} \
template <typename Dtype, typename U> \
inline auto operator op(const Dtype& a, const Expression<Dtype, U>& b) -> decltype(name##LeftExpr<Dtype, U>(a, b.cast())) { \
  return name##RightExpr<Dtype, U>(a, b.value()); \
}
ADOUBLE_ARITHMETIC_OPERATORS_LIST
#undef ADOUBLE_ARITHMETIC_OPERATORS_LIST
#undef OP_ARITHMETIC

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


using adouble = scalar<double>;

}
}

#endif /* __adouble_et_H__ */
