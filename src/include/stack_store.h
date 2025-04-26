/**
 * @file stack_store.h
 * @author Rakesh Kumar (rklsspty777@gmail.com)
 * @brief All the code for storing stack nodes in scopes and functions and other related operations are 
 * placed in this file.
 * @version 0.1.0
 * @date 2025-04-22
 * 
 * 
 */
#pragma once

#include "foundational_macros.h"

/**
 * @brief val_wrapper is a value wrapper, whose instance can be stored on a stack within a scope or a function.
 * The void *p_ref is the generic pointer to the data passed as a pointer.
 * The void *p_mut_ref is initially NULL. The value of p_mut_ref will not be NULL if the type is mutable or if 
 * mutation is diabled when used in a thread.
 * 
 */
struct val_wrapper {
    void *p_ref;                  // pointer to non-mutable reference
    void *p_mut_ref;              // pointer to mutable reference
    struct val_wrapper *prev_item; // pointer to (tos-1)th node of type struct val_wrapper on stack
};

/**
 * @brief This macro takes out the stored value within p_ref void pointer by dereferencing the void pointer.
 * @param stack_node An instance of stack node from which you want to extract value from p_ref.
 */
#define unwrap(p_stack_node) (*((p_stack_node)->p_ref))

/**
 * @brief Enables mutation on a specific data pointed to by the p_ref inside struct val_wrapper.
 * This macro is very useful in context of threads that needs to manipulate data.
 * 
 */
#define enable_mutation(p_fn_var_ref_node) (p_fn_var_ref_node)->p_mut_ref = (p_fn_var_ref_node)->p_ref;

/**
 * @brief Disables mutation on a specific data pointed to by the p_ref inside struct val_wrapper.
 * 
 */
#define disable_mutation(p_fn_var_ref_node) (p_fn_var_ref_node)->p_mut_ref = NULL;

/**
 * @brief Inline Function used as pre-operation before carrying on with other operations on the data.
 * 
 * @param p_fn_var_ref_node A struct val_wrapper wrapper over data.
 * @return void* Pointer to data.
 */
inline void* thread_mut_op_(struct val_wrapper *p_fn_var_ref_node) {
    // check if there is no mutable reference already in use.
    if(p_fn_var_ref_node->p_mut_ref == NULL) {
        /*
        mutable reference don't exist which means it is assumed that no thread is manipulating 
        the underlying data within the struct val_wrapper wrapper. (Ofcourse you are solely responsible for 
        incorrectly manipulating the underlying data within the struct val_wrapper wrapper.)
        */
        // enable mutation
        enable_mutation(p_fn_var_ref_node);
    }
    return p_fn_var_ref_node->p_mut_ref;
}
/**
 * @brief This macro takes out the data pointer by unwrapping and casting to the type provided in macro 
 * argument. Actual data has to be retrieved by dereferencing the void* p_ref.
 * 
 * @param type The type to cast the data to.
 * @param p_fn_var_ref_node pointer to function variable reference node within the stack
 * 
 */
#define thread_mut_op(type, p_fn_var_ref_node) cast(type, unwrap(p_fn_var_ref_node))


/**
 * @brief Registers a pointer within this scope.
 * 
 * @param tos_ref reference to the top-of-stack utilized within the scope.
 * @param ptr_to_be_registered the pointer sent from the calling scope that needs to be registered.
 */
#define reg_fn_var_ref(tos, ref_to_be_registered) { \
    struct val_wrapper *temp = *tos; \
    if(temp != NULL) { \
        /* add to the next node */ \
        temp->prev_item = &((struct val_wrapper){ref_to_be_registered, NULL}); \
    } else { \
        /* add to the current node */ \
        temp->p_ref = ref_to_be_registered; \
        disable_mutation(temp) \
        temp->prev_item = NULL; \
    } \
}


/**
 * @brief Unlike typical pop operation, here the reference pointer(p_ref) within the struct val_wrapper is destroyed and never 
 * returned because a popping operation on a stack removes the contents of top of stack and the reference pointer depends on its 
 * condittional flags present within the struct val_wrapper which dictate the lifecycle of the reference pointer.
 * 
 */
#define pop_fn_var_stack_by_one(tos) { \
    free((*tos)->p_ref); \
    (*tos)->p_ref = NULL; \
}

#define pop_fn_var_stack_all(tos) { \
    while((*tos) != NULL) { \
        pop_fn_var_stack_by_one(tos); \
        *tos = (*tos)->prev_item; \
    } \
}
