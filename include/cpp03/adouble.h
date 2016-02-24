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


#ifndef __oo_no_friend
#define __oo_friends_activate
#include <util/macro_oo_friend.h>
#else
#include <util/macro_oo.h>
#endif

#include "adouble_base.inc"

#undef __noop
#undef __comma
#undef __oo_value_friend
#undef __oo_value
#undef __binary_declaration_template
#undef __binary_definition_template
#undef __unary_declaration_template
#undef __unary_definition_template
#undef __binary_self_definition
#undef __unary_unitstep_definition
#undef __math_2_special_declaration
#undef __math_2_special_definition_template

#undef __oo_binary_op_decl
#undef __oo_binary_op
#undef __oo_binary_cmp_op_decl
#undef __oo_binary_cmp_op
#undef __oo_unary_op_decl
#undef __oo_math_decl
#undef __oo_math
#undef __oo_math_std
#undef __oo_math_decl_2
#undef __oo_math_2
#undef __oo_math_2_std
#undef __oo_math_2_special_decl
#undef __oo_math_2_special
#undef __oo_self_binary_op
#undef __oo_unitstep_op

#endif /* ADOUBLE_H_ */
