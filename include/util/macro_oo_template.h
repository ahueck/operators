/*
 * macro_oo.h
 *
 *  Created on: Feb 23, 2016
 *      Author: ahueck
 */

#ifndef MACRO_OO_TEMPLATE_H_
#define MACRO_OO_TEMPLATE_H_

#define __noop
#define __comma ,

#define __oo_value_friend(var) var.a
#define __oo_value(var) var.value()

#define __binary_declaration_template(ret_type, type, function) \
  ret_type function (const a##type& a, const a##type& b); \
  ret_type function (const type& a, const a##type& b); \
  ret_type function (const a##type& a, const type& b);

#define __binary_definition_template(ret_type, type, function, inner, op, value, pre_keywords, post_keywords) \
  pre_keywords ret_type function (const a##type& a, const a##type& b) post_keywords { \
    return ret_type( inner(value(a) op value(b)) ); \
  } \
  pre_keywords ret_type function (const type& a, const a##type& b) post_keywords { \
    return ret_type( inner(a op value(b)) ); \
  } \
  pre_keywords ret_type function (const a##type& a, const type& b) post_keywords { \
    return ret_type( inner(value(a) op b) ); \
  }

#define __unary_declaration_template(type, function) \
    a##type function (const a##type& a); \

#define __unary_definition_template(type, function, inner, value, pre_keywords, post_keywords) \
  pre_keywords a##type function (const a##type& a) post_keywords { \
    return a##type( inner(value(a)) ); \
  }

#define __binary_self_definition(type, op) \
  inline void operator op (const type& b) { \
    a op b; \
  } \
  inline void operator op (const a##type& b) { \
    a op b.a; \
  }

#define __unary_unitstep_definition(type, op) \
  a##type& operator op () { \
    a op; \
    return *this; \
  } \
  a##type operator op (int) { \
    return a##type( op a ); \
  }

#define __math_2_special_declaration(type, f) \
  a##type f (const int a, const a##type& b);

#define __math_2_special_definition_template(type, f, value, pre_keywords, post_keywords) \
  pre_keywords a##type f (const int a, const a##type& b) post_keywords { \
    return a##type( f(a, value(b)) ); \
  }
#endif /* MACRO_OO_H_ */
