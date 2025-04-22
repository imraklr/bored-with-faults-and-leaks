/**
 * @file fn_stack_data_references.h
 * @author Rakesh Kumar (rklsspty777@gmail.com)
 * @brief This file contains all the ingredients needed to make a macro-based program in C which will be secure in memory management. 
 * @version 0.1.0
 * @date 2025-03-18
 * 
 * 
 */
#pragma once

#include "basic_types.h"

/**
 * @brief Hoisted pointers are pointers that are hoisted out of the function that created it. Each function out 
 * of the scope of the function that created the hoisted pointers can utilize that hoisted pointers within 
 * themselves but the hoisted pointers still follow the ownership model.
 * 
 */
struct fn_var_ref {
    void *ref_ptr;
    struct {
        u8 flags;
        union {
            u8 ref_extra_flag1: 1;       // Extra Placeholder flag (Not In Use)
            u8 ref_extra_flag2: 1;       // Extra Placeholder flag (Not In Use)
            u8 ref_extra_flag3: 1;       // Extra Placeholder flag (Not In Use)
            u8 ref_extra_flag4: 1;       // Extra Placeholder flag (Not In Use)
            u8 ref_extra_flag5: 1;       // Extra Placeholder flag (Not In Use)

            u8 ref_referenced: 1;        // Indicates whether the reference pointer is currently referenced somewhere.
            u8 ref_mutable_referenced: 1;// Indicates whether there is a mutable reference to this data pointed to by void *ref_ptr.
            u8 ref_ptr_dyn_alloc: 1;     // Indicates whether the reference pointer was dynamically allocated. Only dynamically created pointers can be freed by call to free function.
        };
    };

    // Make a stack
    struct fn_var_ref *prev_item;            // Previous item in the function stack references stack
};

/**
 * @brief This macro takes out the stored value within ref_ptr void pointer by dereferencing the void pointer.
 * @param stack_node An instance of stack node from which you want to extract value from ref_ptr.
 */
#define unwrap(stack_node, cast_name) ((cast_name)(*(stack_node.ref_ptr)))


// using macro to define function in global scope
#define fn(return_type, name, ...) return_type name (struct fn_var_ref **tos, ##__VA_ARGS__)


/**
 * @brief Registers a pointer within this scope.
 * 
 * @param tos_ref reference to the top-of-stack utilized within the scope.
 * @param ptr_to_be_registered the pointer sent from the calling scope that needs to be registered.
 */
#define reg_fn_var_ref_(tos, ref_to_be_registered, variable_flags) { \
    struct fn_var_ref *temp = *tos; \
    if(temp != NULL) { \
        /* add to the next node */ \
        temp->prev_item = &((struct fn_var_ref){ref_to_be_registered, {variable_flags}, NULL}); \
    } else { \
        /* add to the current node */ \
        temp->ref_ptr = ref_to_be_registered; \
        temp->flags = variable_flags; \
        temp->prev_item = NULL; \
    } \
}


/**
 * @brief Unlike typical pop operation, here the reference pointer(ref_ptr) within the struct fn_var_ref is destroyed and never 
 * returned because a popping operation on a stack removes the contents of top of stack and the reference pointer depends on its 
 * condittional flags present within the struct fn_var_ref which dictate the lifecycle of the reference pointer.
 * 
 */
#define pop_fn_var_stack_by_one_(tos) { \
    if(((*tos)->flags) & (0xe) == 0) { \
        if(((*tos)->flags) & (0x01) == 0) { \
            free((*tos)->ref_ptr); \
        } \
    } \
    (*tos)->ref_ptr = NULL; \
}

#define pop_fn_var_stack_all_(tos) { \
    while((*tos) != NULL) { \
        pop_fn_var_stack_by_one_(tos); \
        *tos = (*tos)->prev_item; \
    } \
}



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