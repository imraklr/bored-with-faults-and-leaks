/**
 * @file scopes.h
 * @author Rakesh Kumar (rklsspty777@gmail.com)
 * @brief All code related to scopes.
 * @version 0.1.0
 * @date 2025-04-20
 * 
 * 
 */
#pragma once

#include "stack_store.h"
#include "foundational_macros.h"


/**
 * @brief Macro to create a non-labeled lexical scope with unit code inside it.
 * 
 */
#define lexical_scope(scope_name, scope_code) { \
	struct val_wrapper *p_tos_of_##scope_name = NULL; \
	struct val_wrapper **pp_tos_of_##scope_name = &p_tos_of_##scope_name; \
	scope_code \
	pop_fn_var_stack_all(pp_tos_of_##scope_name) \
}

/**
 * @brief Macro to nest scopes.
 * 
 */
#define scope_nest(scope_nest) { \
	scope_nest; \
	/* free the referenced pointers */ \
}