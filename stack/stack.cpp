#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "../include/stack.h"
#include "../include/print.h"
#include "../include/canary.h"
#include "../include/hash.h"

#warning lag constant here and nafig this function

unsigned int increase_stack(const size_t increase_coef, struct Stack* const stk_ptr)
{

	elem_t* old_data_ptr = stk_ptr->data;

	//stk_ptr->data = (elem_t*) realloc(stk_ptr->data, sizeof(elem_t) * stk_ptr->capacity * increase_coef);

	stk_ptr->data = alloc_data(stk_ptr->capacity, stk_ptr->capacity * increase_coef, stk_ptr->data);

	if (stk_ptr->data == NULL)
	{
		stk_ptr->data = old_data_ptr;
		PRINT_STACK_ERR("unable to increase stack\n");

		return UNABLE_TO_INCREASE_STACK;
	}

	stk_ptr->capacity *= increase_coef;

	for (ssize_t elem_number = stk_ptr->capacity / 2; elem_number < stk_ptr->capacity; elem_number++)
	{
		stk_ptr->data[elem_number] = POISON_VALUE;
	}

	return NO_ERROR;
}


unsigned int decrease_stack(const size_t decrease_coef, struct Stack* const stk_ptr)
{
	if (stk_ptr->capacity / decrease_coef < stk_ptr->size)
	{
		PRINT_STACK_ERR("unable to decrease stack, size bigger than capacity to be decreased\n");

		return UNABLE_TO_DECREASE_STACK | STACK_SIZE_LARGER_THAN_CAPACITY;
	}
	
	elem_t* old_data_ptr = stk_ptr->data;

	//stk_ptr->data = (elem_t*) realloc(stk_ptr->data, sizeof(elem_t) * stk_ptr->capacity / decrease_coef);

	stk_ptr->data = alloc_data(stk_ptr->capacity, stk_ptr->capacity / decrease_coef, stk_ptr->data);

	if ((stk_ptr->data) == NULL)
	{
		stk_ptr->data = old_data_ptr;
		PRINT_STACK_ERR("unable to decrease stack\n");

		return UNABLE_TO_DECREASE_STACK;
	}	

	stk_ptr->capacity /= decrease_coef;

	return NO_ERROR;
}


unsigned int stack_push(struct Stack* const stk_ptr, const elem_t value)
{
	const size_t increase_coef = 2;

	unsigned int return_code = stack_verificator(stk_ptr);

	if (return_code != 0)
	{
		PRINT_STACK_ERR("unable to push, invalid stack\n");

		print_stack_error(return_code);

		return return_code;
	}

	if (stk_ptr->size == stk_ptr->capacity)
	{
		return_code |= increase_stack(increase_coef, stk_ptr);

		if (return_code != NO_ERROR)
		{
			print_stack_error(return_code);
			return return_code;
		}

	}

	stk_ptr->data[stk_ptr->size] = value;

	stk_ptr->size++;

	return NO_ERROR;
}


unsigned int stack_pop(struct Stack* const stk_ptr)
{
	const size_t decrease_coef = 2;

	unsigned int return_code = stack_verificator(stk_ptr);

	if (return_code != 0)
	{
		PRINT_STACK_ERR("unable to pop, invalid stack\n");

		print_stack_error(return_code);

		return return_code;
	}

	if (stk_ptr->size == 0)
	{
		PRINT_STACK_ERR("unable to pop, empty stack\n");

		return INVALID_STACK_SIZE;
	}

	ssize_t stack_decrease_lag = get_stack_decrease_lag(stk_ptr->capacity);

	printf("stack size is %zd\n", stk_ptr->size);
	printf("stack capacity is %zd, stack lag is %zd\n", stk_ptr->capacity, stack_decrease_lag);

	#warning lag works wrong way
	if ((stk_ptr->capacity - get_stack_decrease_lag(stk_ptr->capacity)) > stk_ptr->size)
	{
		return_code |= decrease_stack(decrease_coef, stk_ptr);

		if (return_code != NO_ERROR)
		{
			PRINT_STACK_ERR("unable to decrease stack, stack works with the previos size\n");
		}
	}

	stk_ptr->last_popped_value = stk_ptr->data[stk_ptr->size - 1];

	stk_ptr->data[stk_ptr->size - 1] = POISON_VALUE;

	stk_ptr->size--;

	return return_code;
}


enum error_code stack_init(struct Stack* const stk_ptr, const ssize_t start_size)
{

	printf("start stack init\n");

	if (start_size < 0)
	{
		return INVALID_STACK_CAPACITY;
	}

	stk_ptr->capacity = start_size;

	#ifdef CANARY_PROTECTION

		stk_ptr->left_canary = CANARY_LEFT_CONSTANT;

		stk_ptr->right_canary = CANARY_RIGHT_CONSTANT;

	#endif /* CANARY_PROTECTION */

	#ifdef HASH_PROTECTION


		stk_ptr->hash_stack =  calc_hash_stack(*stk_ptr);

		stk_ptr->hash_data  =  calc_hash_data(*stk_ptr);

	#endif /* HASH_PROTECTION */

	stk_ptr->capacity = start_size;

	stk_ptr->last_popped_value = POISON_VALUE;

	stk_ptr->data = init_data(stk_ptr->capacity);

	printf("calloc data\n");

	stk_ptr->size = 0;

	get_stack_init_info();

	return NO_ERROR;
}


enum error_code stack_dtor(struct Stack* stk_ptr)
{
	stk_ptr->capacity = -1;
	stk_ptr->size = -1;

	#warning do not always pooop in user's console
	printf("nulled size and capacity\n");

	free_data(stk_ptr->data);

	stk_ptr->data = 0;

	printf("nulled and free data\n");

	stk_ptr = 0;

	printf("nulled stack pointer\n");

	return NO_ERROR;
}


unsigned int stack_verificator(const struct Stack* const stk_ptr) 
{
	unsigned int return_code = 0;

	printf("start checking stack\n");

	if (stk_ptr == NULL)
	{
		return_code |= STACK_POINTER_IS_NULL;

		return return_code;
	}

	if (stk_ptr->data == NULL)    			return_code |= STACK_DATA_IS_NULL;

	if (stk_ptr->size < 0) 					return_code |= INVALID_STACK_SIZE;

	if (stk_ptr->capacity < 0)              return_code |= INVALID_STACK_CAPACITY;

	if (stk_ptr->size > stk_ptr->capacity)  return_code |= STACK_SIZE_LARGER_THAN_CAPACITY;
	

	#ifdef CANARY_PROTECTION

		if (*get_left_canary_ptr(stk_ptr->data)  != CANARY_LEFT_CONSTANT)  					  return_code |= LEFT_CANARY_DATA_DIED;

		if (*get_right_canary_ptr(stk_ptr->data, stk_ptr->capacity) != CANARY_RIGHT_CONSTANT) return_code |= RIGHT_CANARY_DATA_DIED; 

		if (stk_ptr->left_canary != CANARY_LEFT_CONSTANT)        							  return_code |= LEFT_CANARY_STACK_DIED;

		if (stk_ptr->right_canary != CANARY_RIGHT_CONSTANT)    								  return_code |= RIGHT_CANARY_STACK_DIED;

	#endif /* CANARY_PROTECTION */

	#ifdef HASH_PROTECTION

		if (stk_ptr->hash_stack != calc_hash_stack(*stk_ptr))  return_code |= STACK_HASH_IS_WRONG;

		if (stk_ptr->hash_data  != calc_hash_data(*stk_ptr))   return_code |= DATA_HASH_IS_WRONG;

	#endif /* HASH_PROTECTION */

	return return_code;
}


ssize_t get_stack_decrease_lag(const ssize_t capacity)
{
	const ssize_t lag_constant = 2;

	assert(lag_constant > 0);

	return capacity / lag_constant;
}