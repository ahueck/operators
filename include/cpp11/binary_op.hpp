/*
 * BinaryOp.hpp
 *
 *  Created on: Feb 23, 2016
 *      Author: ahueck
 */

#ifndef BINARYOP_HPP_
#define BINARYOP_HPP_

#define __noop
#define __comma ,

#define BIN_OP(name, function, inner, op) \
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
  auto value() const -> decltype(inner(t.value() op u.value())) { \
    return inner(t.value() op u.value());  \
  } \
};\
  \
template <typename Dtype, typename T, typename U> \
inline auto function(const Expression<Dtype, T>& a, const Expression<Dtype, U>& b) -> decltype(name##Expr<Dtype, T, U>(a.cast(), b.cast())) { \
  return name##Expr<Dtype, T, U>(a.cast(), b.cast()); \
}


#define BIN_OP_L(name, function, inner, op) \
template<typename Dtype, typename T, typename U> \
class name##LeftExpr: public Expression<Dtype, name##LeftExpr<Dtype, T, U>> { \
private: \
  const T& t; \
  const typename TypeTraits<Dtype>::type u; \
public: \
  explicit name##LeftExpr(const Expression<Dtype, T>& a, typename TypeTraits<Dtype>::cref_type b) \
    : t(a.cast()) \
    , u(b) \
  { \
  } \
  auto value() const -> decltype(inner(t.value() op u)) { \
    return inner(t.value() op u); \
  } \
}; \
  \
template <typename Dtype, typename T, typename U> \
inline auto function(const Expression<Dtype, T>& a, typename TypeTraits<Dtype>::cref_type b) -> decltype(name##LeftExpr<Dtype, T, U>(a.cast(), b)) { \
  return name##LeftExpr<Dtype, T, U>(a.cast(), b); \
}

#define BIN_OP_R(name, function, inner, op) \
template<typename Dtype, typename T, typename U> \
class name##RightExpr: public Expression<Dtype, name##RightExpr<Dtype, T, U>> { \
private: \
  const typename TypeTraits<Dtype>::type t; \
  const U& u; \
public: \
  explicit name##RightExpr(typename TypeTraits<Dtype>::cref_type a, const Expression<Dtype, T>& b) \
    : t(a) \
    , u(b.cast()) \
  { \
  } \
  auto value() const -> decltype(inner(t op u.value())) { \
    return inner(t op u.value()); \
  } \
}; \
  \
template <typename Dtype, typename T, typename U> \
inline auto function(const Expression<Dtype, T>& a, typename TypeTraits<Dtype>::cref_type b) -> decltype(name##LeftExpr<Dtype, T, U>(a, b.cast())) { \
  return name##RightExpr<Dtype, T, U>(a, b.value()); \
}

#define __binary_op_cmpl(op) \
  template <typename Dtype, typename T> \
  inline auto operator op(const Expression<Dtype, T>& a, typename TypeTraits<Dtype>::cref_type b) -> decltype(a.value() op b) { \
    return a.value() op b; \
  } \
  template <typename Dtype, typename U> \
  inline auto operator op(typename TypeTraits<Dtype>::cref_type a, const Expression<Dtype, U>& b) -> decltype(a op b.value()) { \
    return a op b.value(); \
  } \
  template <typename Dtype, typename T, typename U> \
  inline auto operator op(const Expression<Dtype, T>& a, const Expression<Dtype, U>& b) -> decltype(a.value() op b.value()) { \
    return a.value() op b.value(); \
  }


#define __trans_math_2(name, function) \
    BIN_OP_L(name, function, function,  __comma) \
    BIN_OP(name, function, function,  __comma) \
    BIN_OP_R(name, function, function,  __comma)

#define __trans_math_2_std(name, function) \
    BIN_OP_L(name, function, std::function,  __comma) \
    BIN_OP(name, function, std::function,  __comma) \
    BIN_OP_R(name, function, std::function,  __comma)

#define __binary_op(name, op) \
    BIN_OP_L(name, operator op, __noop, op) \
    BIN_OP(name, operator op, __noop, op) \
    BIN_OP_R(name, operator op, __noop, op) \


#endif /* BINARYOP_HPP_ */
