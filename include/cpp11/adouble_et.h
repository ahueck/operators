/*
 * adouble_et.h
 *
 *  Created on: Feb 22, 2016
 *      Author: ahueck
 */

#ifndef CPP11_ADOUBLE_ET_H
#define CPP11_ADOUBLE_ET_H

#include <iostream>
#include <type_traits>
#include <cmath>

#define ADOUBLE_CMP_OPERATORS_LIST \
  OP_CMP(==) \
  OP_CMP(!=) \
  OP_CMP(>=) \
  OP_CMP(<=) \
  OP_CMP(<) \
  OP_CMP(>)

#define ADOUBLE_ARITHMETIC_OPERATORS_LIST \
  OP_ARITHMETIC_HELPER(Add, +) \
  OP_ARITHMETIC_HELPER(Sub, -) \
  OP_ARITHMETIC_HELPER(Mul, *) \
  OP_ARITHMETIC_HELPER(Div, /) \
  OP_BINARY(Add, operator +, AddHelper) \
  OP_BINARY(Sub, operator -, SubHelper) \
  OP_BINARY(Mul, operator *, MulHelper) \
  OP_BINARY(Div, operator /, DivHelper)

#define ADOUBLE_UNITSTEP_OPERATORS_LIST \
  OP_UNITSTEP(++) \
  OP_UNITSTEP(--)

#define ADOUBLE_UNARY_OPERATORS_LIST \
  OP_UNARY(UnaryMinus, operator-, -)

#define ADOUBLE_UNARY_MATH_LIST \
  OP_UNARY(Round, round, std::round) \
  OP_UNARY(Ceil, ceil, std::ceil) \
  OP_UNARY(Floor, floor, std::floor) \
  OP_UNARY(Fabs, fabs, std::fabs) \
  /* for compatibility: */ \
  OP_UNARY(Abs, abs, std::abs) \
  /* cf. https://www.gnu.org/software/libc/manual/html_node/Exponents-and-Logarithms.html */ \
  OP_UNARY(Exp, exp, std::exp) \
  OP_UNARY(Exp2, exp2, std::exp2) \
  OP_UNARY(Exp10, exp10, exp10) \
  OP_UNARY(Log, log, std::log) \
  OP_UNARY(Log10, log10, std::log10) \
  OP_UNARY(Log2, log2, std::log2) \
  OP_UNARY(Logb, logb, std::logb) \
  OP_UNARY(Sqrt, sqrt, std::sqrt) \
  OP_UNARY(Cbrt, cbrt, std::cbrt) \
  OP_UNARY(Expm1, expm1, std::expm1) \
  OP_UNARY(Log1p, log1p, std::log1p) \
  /* cf. https://www.gnu.org/software/libc/manual/html_node/Trig-Functions.html */ \
  OP_UNARY(Sin, sin, std::sin) \
  OP_UNARY(Cos, cos, std::cos) \
  OP_UNARY(Tan, tan, std::tan) \
  /* OP_UNARY(Sincos, sincos, std::sincos) */ \
  /* cf. https://www.gnu.org/software/libc/manual/html_node/Inverse-Trig-Functions.html */ \
  OP_UNARY(Asin, asin, std::asin) \
  OP_UNARY(Acos, acos, std::acos) \
  OP_UNARY(Atan, atan, std::atan) \
  /* cf. https://www.gnu.org/software/libc/manual/html_node/Hyperbolic-Functions.htm */ \
  OP_UNARY(Sinh, sinh, std::sinh) \
  OP_UNARY(Cosh, cosh, std::cosh) \
  OP_UNARY(Tanh, tanh, std::tanh) \
  OP_UNARY(Asinh, asinh, std::asinh) \
  OP_UNARY(Acosh, acosh, std::acosh) \
  OP_UNARY(Atanh, atanh, std::atanh) \
  /* cf. https://www.gnu.org/software/libc/manual/html_node/Special-Functions.html */ \
  OP_UNARY(Erf, erf, std::erf) \
  OP_UNARY(Erfc, erfc, std::erfc) \
  OP_UNARY(Lgamma, lgamma, std::lgamma) \
  /* Missing: "lgamma_r (double x, int *signp)" */ \
  OP_UNARY(Gamma, gamma, gamma) \
  OP_UNARY(J0, j0, j0) \
  OP_UNARY(J1, j1, j1) \
  OP_UNARY(Y0, y0, y0) \
  OP_UNARY(Y1, y1, y1)

#define ADOUBLE_BINARY_MATH_LIST \
  OP_BINARY(Pow, pow, std::pow) \
  OP_BINARY(Hypot, hypot, std::hypot) \
  OP_BINARY(Atan2, atan2, std::atan2) \
  OP_BINARY(Fmin, fmin, std::fmin) \
  OP_BINARY(Fmax, fmax, std::fmax) \
  OP_BINARY(Min, min, std::min) \
  OP_BINARY(Max, max, std::max)


template<typename T>
class TypeTraits {
public:
  typedef typename std::remove_reference<T>::type type;
  typedef type& ref_type;
  typedef type const &cref_type;
};

template<typename Dtype, typename T>
class Expression {
public:
  Expression(const Expression&) = delete;

  Expression& operator=(const Expression&) = delete;

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

  scalar(const Dtype& a) : data(a) {
  }

  template<typename T>
  scalar(const Expression<Dtype, T>& a) : data(a.value()) {
  }

  scalar(const scalar<Dtype>& a) : data(a.data) {
  }

  auto value() const -> Dtype {
    return data;
  }

  auto operator=(const Dtype& a) -> scalar<Dtype>& {
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

#define OP_UNITSTEP(OP_) \
  auto operator OP_ () -> scalar<Dtype>& { \
    OP_ a; \
    return *this; \
  } \
  auto operator OP_ (int) -> scalar<Dtype>& { \
	scalar<Dtype> res(a); \
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
#undef OP_CMP


#define OP_UNARY(name, F_, INNER_F_) \
template<typename Dtype, typename T> \
class name##Expr: public Expression<Dtype, name##Expr<Dtype, T>> { \
private: \
  const T& t; \
public: \
  explicit name##Expr(const Expression<Dtype, T>& a) \
    : t(a.cast()) \
  { \
  } \
  auto value() const -> decltype(INNER_F_(t.value())) { \
    return INNER_F_(t.value()); \
  } \
}; \
\
template <typename Dtype, typename T> \
auto F_(const Expression<Dtype, T>& a) -> decltype(name##Expr<Dtype, T>(a.cast())) { \
  return name##Expr<Dtype, T>(a.cast()); \
}
ADOUBLE_UNARY_OPERATORS_LIST
#undef ADOUBLE_UNARY_OPERATORS_LIST
ADOUBLE_UNARY_MATH_LIST
#undef ADOUBLE_UNARY_MATH_LIST
#undef OP_UNARY


#define OP_ARITHMETIC_HELPER(NAME, OP_) \
  template<typename T, typename U> \
  inline auto NAME##Helper(const T& lhs, const U& rhs) -> decltype(lhs OP_ rhs) { \
    return lhs OP_ rhs; \
  }

#define OP_BINARY(NAME, F_, INNER_F_) \
template<typename Dtype, typename T, typename U> \
class NAME##Expr: public Expression<Dtype, NAME##Expr<Dtype, T, U>> { \
private: \
  const T& t; \
  const U& u; \
public: \
  explicit NAME##Expr(const Expression<Dtype, T>& a, const Expression<Dtype, U>& b) \
    : t(a.cast()) \
    , u(b.cast()) \
  { \
  } \
  auto value() const -> decltype(INNER_F_(t.value(), u.value())) { \
    return INNER_F_(t.value(), u.value());  \
  } \
};\
template<typename Dtype, typename T> \
class NAME##LeftExpr: public Expression<Dtype, NAME##LeftExpr<Dtype, T>> { \
private: \
  const T& t; \
  const Dtype u; \
public: \
  explicit NAME##LeftExpr(const Expression<Dtype, T>& a, const Dtype& b) \
    : t(a.cast()) \
    , u(b) \
  { \
  } \
  auto value() const -> decltype(INNER_F_(t.value(), u)) { \
    return INNER_F_(t.value(), u); \
  } \
}; \
template<typename Dtype, typename U> \
class NAME##RightExpr: public Expression<Dtype, NAME##RightExpr<Dtype, U>> { \
private: \
  const Dtype t; \
  const U& u; \
public: \
  explicit NAME##RightExpr(const Dtype& a, const Expression<Dtype, T>& b) \
    : t(a) \
    , u(b.cast()) \
  { \
  } \
  auto value() const -> decltype(INNER_F_(t, u.value())) { \
    return INNER_F_(t, u.value()); \
  } \
}; \
template <typename Dtype, typename T, typename U> \
inline auto F_(const Expression<Dtype, T>& a, const Expression<Dtype, U>& b) -> decltype(NAME##Expr<Dtype, T, U>(a.cast(), b.cast())) { \
  return NAME##Expr<Dtype, T, U>(a.cast(), b.cast()); \
} \
template <typename Dtype, typename T> \
inline auto F_(const Expression<Dtype, T>& a, const Dtype& b) -> decltype(NAME##LeftExpr<Dtype, T>(a.cast(), b)) { \
  return NAME##LeftExpr<Dtype, T>(a.cast(), b); \
} \
template <typename Dtype, typename U> \
inline auto F_(const Dtype& a, const Expression<Dtype, U>& b) -> decltype(NAME##LeftExpr<Dtype, U>(a, b.cast())) { \
  return NAME##RightExpr<Dtype, U>(a, b.value()); \
}
ADOUBLE_ARITHMETIC_OPERATORS_LIST
#undef ADOUBLE_ARITHMETIC_OPERATORS_LIST
#undef OP_ARITHMETIC_HELPER
ADOUBLE_BINARY_MATH_LIST
#undef ADOUBLE_BINARY_MATH_LIST
#undef OP_BINARY


using adouble = scalar<double>;

#endif /* CPP11_ADOUBLE_ET_H */
