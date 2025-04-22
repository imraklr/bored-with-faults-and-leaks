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

void func_to_use(struct fn_var_ref **tos) {
	int *p = (int*)malloc(sizeof(int));
	reg_fn_var_ref(tos, p);
	*p = 24;
	printf("Address of p = %p\n", p);
}


int main() {

	owner_void_scope(func_to_use)

	return 0;
}
