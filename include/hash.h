#ifndef HASH_H
	#define HASH_H

	#ifdef HASH_PROTECTION

		unsigned int calc_hash_stack(struct Stack* const stk_ptr);
		unsigned int  calc_hash_data(struct Stack* const stk_ptr);

	#endif /* HASH_PROTECTION */

#endif /* HASH_H */ 