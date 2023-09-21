#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "include/stack.h"
#include "include/print.h"


unsigned int increase_stack(const size_t increase_coef, struct Stack* const stk_ptr)
{

	elem_t* old_data_ptr = stk_ptr->data;

	stk_ptr->data = (elem_t*) realloc(stk_ptr->data, sizeof(elem_t) * stk_ptr->capacity * increase_coef);

	if (stk_ptr->data == NULL)
	{
		stk_ptr->data = old_data_ptr;
		printf("unable to increase stack\n");

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
		printf("unable to decrease stack, size bigger than capacity to be decreased\n");

		return UNABLE_TO_DECREASE_STACK | STACK_SIZE_LARGER_THAN_CAPACITY;
	}
	
	elem_t* old_data_ptr = stk_ptr->data;

	stk_ptr->data = (elem_t*) realloc(stk_ptr->data, sizeof(elem_t) * stk_ptr->capacity / decrease_coef);

	if ((stk_ptr->data) == NULL)
	{
		stk_ptr->data = old_data_ptr;
		printf("unable to decrease stack\n");

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
		printf("unable to push, invalid stack\n");

		print_error(return_code);

		return return_code;
	}

	if (stk_ptr->size == stk_ptr->capacity)
	{
		unsigned int return_code = increase_stack(increase_coef, stk_ptr);

		if (return_code != NO_ERROR)
		{
			print_error(return_code);
			return return_code;
		}

	}

	stk_ptr->data[stk_ptr->size] = value;

	stk_ptr->size++;

	return NO_ERROR;
}


unsigned int stack_pop(struct Stack* const stk_ptr, elem_t* const value_ptr)
{
	const size_t decrease_coef = 2;

	unsigned int return_code = stack_verificator(stk_ptr);

	if (return_code != 0)
	{
		printf("unable to pop, invalid stack\n");

		print_error(return_code);

		return return_code;
	}

	if (stk_ptr->size == 0)
	{
		printf("unable to pop, empty stack\n");

		return INVALID_STACK_SIZE;
	}

	*value_ptr = stk_ptr->data[stk_ptr->size];

	stk_ptr->data[stk_ptr->size - 1] = POISON_VALUE;

	stk_ptr->size--;

	return NO_ERROR;
}


enum error_code stack_init(struct Stack* const stk_ptr, const ssize_t start_size)
{

	printf("start stack init\n");

	if (start_size < 0)
	{
		return INVALID_STACK_CAPACITY;
	}

	stk_ptr->capacity = start_size;

	stk_ptr->data = (elem_t*) calloc(stk_ptr->capacity, sizeof(elem_t));

	printf("calloc data\n");

	stk_ptr->size = 0;

	get_stack_init_info();

	return NO_ERROR;
}


enum error_code stack_dtor(struct Stack* stk_ptr)
{
	stk_ptr->capacity = -1;
	stk_ptr->size = -1;

	printf("nulled size and capacity\n");

	free(stk_ptr->data);

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

	if (stk_ptr->data == NULL)
	{
		return_code |= STACK_DATA_IS_NULL;
	}

	if (stk_ptr->size < 0)
	{
		return_code |= INVALID_STACK_SIZE;
	}

	if (stk_ptr->capacity < 0)
	{
		return_code |= INVALID_STACK_CAPACITY;
	}

	if (stk_ptr->size > stk_ptr->capacity)
	{
		return_code |= STACK_SIZE_LARGER_THAN_CAPACITY;
	}

	return return_code;
}