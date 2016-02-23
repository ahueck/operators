/*
 * macro_oo.h
 *
 *  Created on: Feb 23, 2016
 *      Author: ahueck
 */

#ifndef MACRO_OO_H_
#define MACRO_OO_H_

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
#endif /* MACRO_OO_H_ */
