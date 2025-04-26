/**
 * @file main.c
 * @author Rakesh Kumar (rklsspty777@gmail.com)
 * @brief Sample executable program to test out the secure contructs.
 * @version 0.1.0
 * @date 2025-04-22
 * 
 * 
 */
#include <stdio.h>
#include <stdlib.h>

#include "include/foundations.h"

void func_to_use(struct val_wrapper **tos) {}


int main() {

	// TODO: Mind the point 3 from the pen-paper notes
	lexical_scope(func_to_use, {
		int *p = (int*)malloc(sizeof(int)); *p = 24;
		// reg_fn_var_ref(tos, p); // give scope alternative
		printf("Address of p = %p\n", p);
	})

	return 0;
}
