#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ingredients/include/ingredients.h"
#include "ingredients/include/variables.h"
#include "ingredients/include/basic_types.h"
#include "ingredients/include/scopes.h"

#if defined(WIN32) || defined(_WIN32)
	#include <Windows.h>
#endif

void func_to_use(struct fn_var_ref **tos) {
	int *p = (int*)malloc(sizeof(int));
	reg_fn_var_ref_(tos, p, 0x01);
	*p = 24;
	printf("Address of p = %p\n", p);
}


int main() {

	owner_void_scope(func_to_use)

	return 0;
}
