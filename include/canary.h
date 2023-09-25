#ifndef CANARY_H
	#define CANARY_H

	#include "stack.h"


	#ifdef CANARY_PROTECTION

		

		const elem_t CANARY_LEFT_CONSTANT = 1253;
		const elem_t CANARY_RIGHT_CONSTANT = 3521;

		canary_t* get_right_canary_ptr(elem_t* const data, ssize_t capacity);
		canary_t* get_left_canary_ptr(elem_t* const data);

	#endif /* CANARY_PROTECTION */

	elem_t* alloc_data(const ssize_t old_capacity, const ssize_t new_capacity, elem_t* data);

	elem_t* init_data(const ssize_t capacity);
	unsigned int free_data(elem_t* data);

#endif /* CANARY_H */		