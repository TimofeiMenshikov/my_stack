#include <stdio.h>
#include <assert.h>
#include "include/print.h"
#include "include/stack.h"

unsigned int print_stack(const Stack* const stk_ptr, ssize_t print_poison_data_count)
{
	unsigned int return_code = stack_verificator(stk_ptr);

	printf("stack stk\n");

	if (return_code != 0)
	{
		printf("stack is not work correct\n");

		print_error(return_code);

		return return_code;
	}

	printf("{\n");
	printf("\tstack information\n");

	printf("\t{\n");
	printf("\t\twhere init:\n");
	printf("\t\t  line: %d\n", stk_ptr->stk_info.init_line);
	printf("\t\t  func: %s\n", stk_ptr->stk_info.init_func);
	printf("\t\t  file: %s\n", stk_ptr->stk_info.init_file);

	putchar('\n');

	printf("\t\twhere called:\n");
	printf("\t\t  line: %d\n", stk_ptr->stk_info.call_line);
	printf("\t\t  func: %s\n", stk_ptr->stk_info.call_func);
	printf("\t\t  file: %s\n", stk_ptr->stk_info.call_file);
	
	printf("\t}\n");


	printf("\tsize = %zd\n", stk_ptr->size);
	printf("\tcapacity = %zd\n", stk_ptr->capacity);

	print_data(stk_ptr, print_poison_data_count);



	printf("}\n");

	return NO_ERROR;
}



unsigned int print_data(const struct Stack* const stk_ptr, ssize_t print_poison_data_count)
{
	printf("\tdata [%p]\n", stk_ptr->data);
	printf("\t{\n");

	if (print_poison_data_count > (stk_ptr->capacity - stk_ptr->size)) // print_poison_data_count - сколько элементов, не находящихся в стеке нужно вывести. Если таких элементов меньше, то выводится весь массив
	{
		print_poison_data_count = stk_ptr->capacity - stk_ptr->size;
	}

	assert((print_poison_data_count + stk_ptr->size) >= stk_ptr->capacity);

	for (ssize_t element_number = 0; element_number < stk_ptr->size; element_number++)
	{
		printf("\t\t*[%zd] = %d\n", element_number, stk_ptr->data[element_number]);
	}

	for (ssize_t element_number = stk_ptr->size; element_number < (print_poison_data_count +  stk_ptr->size); element_number++)
	{
		printf("\t\t [%zd] = %d\n", element_number, stk_ptr->data[element_number]);       // %d работает, если typedef int !!!!!!!!!!!!!!!!!!!!!!!
	}

	printf("\t}\n");

	return NO_ERROR;
}



unsigned int print_error(unsigned int error_code)
{
	if (error_code == NO_ERROR)
	{
		printf("NO ERROR\n");
		return error_code;
	}

	printf("errors:\n");

	if ((error_code & STACK_POINTER_IS_NULL) 			 != 0) printf("stack pointer is NULL\n");

	if ((error_code & STACK_DATA_IS_NULL)     		     != 0) printf("stack data is NULL\n");

	if ((error_code & INVALID_STACK_SIZE)      		     != 0) printf("stack size is < 0\n");

	if ((error_code & INVALID_STACK_CAPACITY) 		     != 0) printf("stack capacity is < 0\n");

	if ((error_code & STACK_SIZE_LARGER_THAN_CAPACITY)   != 0) printf("stack size is larger than stack capacity\n");


	return error_code;
}