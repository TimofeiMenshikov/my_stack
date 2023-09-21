#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "include/stack.h"
#include "include/print.h"


unsigned int stack_push(struct Stack* const stk_ptr, const elem_t value)
{
	unsigned int return_code = stack_verificator(stk_ptr);

	if (return_code != 0)
	{
		printf("unable to push, invalid stack\n");

		print_error(return_code);

		return return_code;
	}

	if (stk_ptr->size == stk_ptr->capacity)
	{
		printf("unable to push, stack size = stack capacity\n");

		return STACK_SIZE_LARGER_THAN_CAPACITY;
	}

	stk_ptr->data[stk_ptr->size] = value;

	stk_ptr->size++;

	return NO_ERROR;
}


unsigned int stack_pop(struct Stack* stk_ptr, elem_t* value_ptr)
{
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

	value_ptr* = data[stk_ptr->size];

	data[stk_ptr->size] = -1;

	stk_ptr->size--;

	return NO_ERROR;
}

enum error_code stack_init(struct Stack* stk_ptr, const ssize_t start_size)
{

	printf("start stack init\n");

	assert(start_size >= 0);

	stk_ptr->capacity = start_size;

	stk_ptr->data = (elem_t*) calloc(stk_ptr->capacity, sizeof(elem_t));

	printf("calloc data\n");

	stk_ptr->size = 0;

	stk_ptr->stk_info.init_line = __LINE__;

	stk_ptr->stk_info.init_file = __FILE__;

	stk_ptr->stk_info.init_func = __func__;

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