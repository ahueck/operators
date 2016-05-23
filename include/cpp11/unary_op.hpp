/*
 * UnaryOp.hpp
 *
 *  Created on: Feb 23, 2016
 *      Author: ahueck
 */

#ifndef UNARYOP_HPP_
#define UNARYOP_HPP_

#define UN_OP(name, function, op) \
template<typename Dtype, typename T> \
class name##Expr: public Expression<Dtype, name##Expr<Dtype, T>> { \
private: \
  const T& t; \
public: \
  explicit name##Expr(const Expression<Dtype, T>& a) \
    : t(a.cast()) \
  { \
  } \
  auto value() const -> decltype(op(t.value())) { \
    return op(t.value()); \
  } \
}; \
\
template <typename Dtype, typename T> \
auto function(const Expression<Dtype, T>& a) -> decltype(name##Expr<Dtype, T>(a.cast())) { \
  return name##Expr<Dtype, T>(a.cast()); \
}

#define __trans_math(name, function) \
  UN_OP(name, function, function)

#define __trans_math_std(name, function) \
  UN_OP(name, function, std::function)

#define __unary_op_et(name, op) \
  UN_OP(name, operator op, op)


#endif /* UNARYOP_HPP_ */
