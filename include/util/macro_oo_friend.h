/*
 * macro_oo_friend.h
 *
 *  Created on: Feb 24, 2016
 *      Author: ahueck
 */

#ifndef MACRO_OO_FRIEND_H_
#define MACRO_OO_FRIEND_H_

#include "macro_oo_template.h"

#define __oo_binary_op_decl(op) \
  __binary_declaration_template(adouble, double, operator op)
#define __oo_binary_op(op) \
  __binary_definition_template(adouble, double, operator op, __noop, op, __oo_value_friend, friend, __noop)


#define __oo_binary_cmp_op_decl(op) \
  __binary_declaration_template(bool, double, operator op)
#define __oo_binary_cmp_op(op) \
  __binary_definition_template(bool, double, operator op, __noop, op, __oo_value_friend, friend, __noop)


#define __oo_unary_op_decl(op) \
  __unary_declaration_template(double, operator op)
#define __oo_unary_op(op) \
  __unary_definition_template(double, operator op, op, __oo_value_friend, friend, __noop)


#define __oo_math_decl(f) \
  __unary_declaration_template(double, f)
#define __oo_math(f) \
  __unary_definition_template(double, f, f, __oo_value_friend, friend, __noop)
#define __oo_math_std(f) \
  __unary_definition_template(double, f, std::f, __oo_value_friend, friend, __noop)


#define __oo_math_decl_2(f) \
  __binary_declaration_template(adouble, double, f)
#define __oo_math_2(f) \
  __binary_definition_template(adouble, double, f, f, __comma, __oo_value_friend, friend, __noop)
#define __oo_math_2_std(f) \
  __binary_definition_template(adouble, double, f, std::f, __comma, __oo_value_friend, friend, __noop)


#define __oo_math_2_special_decl(f) \
  __math_2_special_declaration(double, f)
#define __oo_math_2_special(f) \
  __math_2_special_definition_template(double, f, __oo_value_friend, friend, __noop)


#define __oo_self_binary_op(op) \
  __binary_self_definition(double, op)


#define __oo_unitstep_op(op) \
  __unary_unitstep_definition(double, op)

#endif /* MACRO_OO_FRIEND_H_ */
