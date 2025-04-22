/**
 * @file variables.h
 * @author Rakesh Kumar (rklsspty777@gmail.com)
 * @brief This file contains code for creating variables, both constant and mutable variables for use in both 
 * scoped and non-scoped code.
 * @version 0.1.0
 * @date 2025-04-17
 * 
 * 
 */
#pragma once

#include "foundational_macros.h"

// constant creation technique ( do not use incomplete types like void ), recommended use: without scope
#define let(type, variable, value) const type variable = value;
// variable creation technique ( do not use incomplete types like void ), recommended use: without scope
#define mut(type, variable, value) type variable = value;
// Note that there is no macro for dynamic allocation of memory for use without scope macro and it is not recommended

// constant creation technique within scope ( do not use incomplete types like void ), recommended use: within scope
#define scope_let(type, variable, value) const type variable = value; \
{ \
    reg_fn_var_ref(&tos, &variable, 0b00000000); \
}
// variable creation technique ( do not use incomplete types like void ), recommended use: within scope
#define scope_mut(type, variable, value) type variable = value; \
{ \
    reg_fn_var_ref(&tos, &variable, 0b00000000); \
}
// dynamic memory management macros for use within the scope macro (the cast_type can be a pointer)
#define scope_mut_malloc(cast_type, variable, size_in_bytes) cast_type variable = (cast_type)malloc(size_in_bytes); { \
    reg_fn_var_ref(&tos, variable, 0b00000001) \
}
#define scope_mut_calloc(cast_type, variable, size_t_num, size_in_bytes) cast_type variable = (cast_type)calloc(size_t_num, size_in_bytes); { \
    reg_fn_var_ref(&tos, variable, 0b00000001) \
}
#define scope_mut_aligned_alloc(cast_type, variable, size_t_alignment, size_in_bytes) cast_type variable = (cast_type)aligned_alloc(alignment, size_in_bytes); { \
    reg_fn_var_ref(&tos, variable, 0b00000001) \
}
// constant variable creation
#define scope_let_malloc(cast_type, variable, size_in_bytes) const scope_mut_malloc(cast_type, variable, size_in_bytes)
#define scope_let_calloc(cast_type, variable, size_t_num, size_in_bytes) const scope_mut_calloc(cast_type, variable, size_t_num, size_in_bytes)
#define scope_let_aligned_alloc(cast_type, variable, size_t_alignment, size_in_bytes) const scope_mut_aligned_alloc(cast_type, variable, size_t_alignment, size_in_bytes)
// realloc can be done only on mutable types
#define scope_mut_realloc(cast_type, variable, new_size_in_bytes) variable = (cast_type)realloc(variable, new_size_in_bytes);