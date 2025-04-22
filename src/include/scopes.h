/**
 * @file scopes.h
 * @author Rakesh Kumar (rklsspty777@gmail.com)
 * @brief All code related to scopes and function-like scopes.
 * @version 0.1.0
 * @date 2025-04-20
 * 
 * 
 */
#pragma once

#include "foundational_macros.h"

/**
 * @brief An ownership scope handles the references owned within it by the calling function.
 * There is one and only one scope per function. Do not nest scope using this macro. If a nested scope is defined 
 * within this macro then you might bug your program.
 * 
 * @note An ownership scope can't output anything i.e. the expression(s) within an ownership scope cannot be assigned 
 * to a variable (initialized with mut macro) or a constant (initialized with let macro).
 * 
 */
#define owner_result_scope(result_store, function, ...) { \
    struct fn_var_ref *p_tos = &tos; \
    struct fn_var_ref **pp_tos = &p_tos; \
	result_store = function(pp_tos, ##__VA_ARGS__); \
	pop_fn_var_stack_all_(pp_tos); \
}

#define owner_void_scope(function, ...) { \
    struct fn_var_ref *p_tos = NULL; \
    struct fn_var_ref **pp_tos = &p_tos; \
	function(pp_tos, ##__VA_ARGS__); \
	pop_fn_var_stack_all_(pp_tos); \
}

#define scope_nest(scope_nest) { \
	scope_nest; \
	/* free the referenced pointers */ \
}