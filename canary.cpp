#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "include/canary.h"
#include "include/stack.h"


#ifdef CANARY_PROTECTION

	canary_t* get_left_canary_ptr(const elem_t* const data)
	{
		canary_t* canary_left_ptr = (canary_t*)data - 1;
		return canary_left_ptr;
	}

	canary_t* get_right_canary_ptr(const elem_t* const data, ssize_t capacity)
	{
		canary_t* canary_right_ptr = (canary_t*)((elem_t*)data + capacity);
		return canary_right_ptr;
	}

#endif /* CANARY_PROTECTION */


unsigned int free_data(elem_t* data)
{
	#ifdef CANARY_PROTECTION
		free(get_left_canary_ptr(data));
	#else /* CANARY_PROTECTION */
		free(data);
	#endif /* CANARY_PROTECTION */

	data = 0;

	return NO_ERROR;
}


elem_t* alloc_data(const ssize_t capacity, elem_t* data)
{
	#ifdef CANARY_PROTECTION
		
		size_t n_bytes = capacity * sizeof(elem_t) + 2 * sizeof(canary_t);

		printf("%zu bytes to calloc\n", n_bytes);


		if (data == 0)
		{
			
			data = (elem_t*)calloc(n_bytes, sizeof(char));
		}
		else
		{
			printf("data is not null\n");
			data = (elem_t*)realloc(get_left_canary_ptr(data), n_bytes * sizeof(char));
		}

		printf("calloc data\n");
		assert(data);

		printf("data after calloc: [%p]\n", data);

		data = (elem_t*)((canary_t*)data + 1);

		printf("data after offset [%p]\n", data);

		canary_t* canary_left_ptr = get_left_canary_ptr(data);

		printf("canary_left_ptr is [%p]\n", canary_left_ptr);

		*canary_left_ptr = CANARY_LEFT_CONSTANT;

		canary_t* canary_right_ptr = get_right_canary_ptr(data, capacity);

		printf("canary_right_ptr is [%p]\n", canary_right_ptr);

		*canary_right_ptr = CANARY_RIGHT_CONSTANT;
	
	#else /* CANARY_PROTECTION */

		size_t n_bytes = capacity * sizeof(elem_t);

		printf("%zu bytes to calloc\n", n_bytes);

		data = (elem_t*) realloc(data, n_bytes);

		assert(data);

	#endif /* CANARY_PROTECTION */	

	for (ssize_t n_elem = 0; n_elem < capacity; n_elem++)
	{
		data[n_elem] = POISON_VALUE;
	}

	return data;	
}


elem_t* init_data(const ssize_t capacity)
{
	elem_t* data = NULL;

	return alloc_data(capacity, data);
}