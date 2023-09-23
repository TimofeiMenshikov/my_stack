#include <stdio.h>
#include "include/hash.h"
#include "include/stack.h"

#ifdef HASH_PROTECTION
	unsigned int calc_hash_stack(struct Stack* const stk_ptr)
	{
		stk_ptr->hash_stack = 0;

		return NO_ERROR;
	}

	unsigned int calc_hash_data(struct Stack* const stk_ptr)
	{
		stk_ptr->hash_data = 0;

		return NO_ERROR;
	}
#endif /* HASH_PROTECTION */
