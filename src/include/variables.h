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

#include <stdio.h>
#include <stdlib.h>

#include "foundational_macros.h"


/**
 * @brief Declares a constant variable.
 *
 * This macro provides a concise way to declare constant variables by automatically prepending the 'const'
 * keyword to the specified type. It's especially helpful for declaring immutable primitive types.
 *
 * @note This macro can be used for both pointer and non-pointer types.
 * @note Use this macro for stack-allocated variables (both objects and primitive types).
 * @note Constants declared with this macro are not placed on the function/scope stack.
 * @note Internally, this macro transforms a declaration like 'int x' into 'const int x', 
 * 'struct some_type *y' into 'const struct some_type *y', etc.
 */
#define let(type, variable, value) const type variable = value;

/**
 * @brief Declares a mutable variable.
 * 
 * @note Use this macro for both pointers as well as non-pointers.
 * @note Use this macro for stack-allocated variables (both objects and primitive types).
 * @note Variables declared with this macro are not placed on the function/scope stack.
 * @note This macro essentially keeps the form of variable declaration like 'int x' to 'int x'.
 */
#define mut(type, variable, value) type variable = value;

/**
 * @brief This macro is used to reuse a variable with some new value stored in it.
 * 
 * @param address Address or variable at which the new value has to be stored.
 * @param value The new value.
 * 
 */
#define reuse(address, value) address = value;


/**
 * @brief Declares a constant variable. 'd' in 'dlet' stands for dynamic/dynamically allocation.
 *
 * This macro provides a concise way to declare constant variables by automatically prepending the 'const'
 * keyword to the specified type. It's especially helpful for declaring immutable primitive types.
 *
 * @note This macro should specifically be used for dynamically created pointers only.
 * @note Use this macro for heap-allocated variables (both objects and primitive types).
 * @note Constants declared with this macro are placed on the function/scope stack.
 * @note Internally, this macro transforms a declaration like 'int x' into 'const int x', 
 * 'struct some_type *y' into 'const struct some_type *y', etc.
 */
#define dlet(type, variable, value) const struct var_ref variable = (struct var_ref){value, NULL, NULL, NULL};

/**
 * @brief Declares a mutable variable. 'd' in 'dmut' stands for dynamic/dynamically allocation.
 * 
 * @note Use this macro for both pointers as well as non-pointers.
 * @note Use this macro for stack-allocated variables (both objects and primitive types).
 * @note Variables declared with this macro are not placed on the function/scope stack.
 * @note This macro essentially keeps the form of variable declaration like 'int x' to 'int x'.
 */
#define dmut(type, variable, value) struct var_ref variable = (struct var_ref){value, NULL, NULL, NULL};

/**
 * @brief This macro is used to reuse a variable with some new value stored in it.
 * @note This macro should be used with dynamically allocated resources.
 * 
 * @param p_wrapper Pointer to wrapper whose data is supposed to be edited.
 * @param value The new value. This value should be a pointer type as it the actual data will be dynamically 
 * allocated.
 * 
 */
#define dreuse(p_wrapper, value) { \
    /* Edit the value within the wrapper iff the data within the wrapper is not in mutative state. */ \
    if((p_wrapper)->p_mut_ref == NULL) { \
        (p_wrapper)->p_ref = value; \
    } else { \
        printf("ERR: Can't modify an existing value in mutative state.\n"); \
        abort(); \
    } \
}