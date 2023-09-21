#ifndef STACK_H
#define STACK_H

typedef int elem_t;


enum error_code
{
	NO_ERROR = 0,
	STACK_POINTER_IS_NULL = 1,
	STACK_DATA_IS_NULL = 2,
	INVALID_STACK_SIZE = 4,
	INVALID_STACK_CAPACITY = 8,
	STACK_SIZE_LARGER_THAN_CAPACITY = 16
};

struct Stack_info
{
	int init_line;
	const char* init_func;
	const char* init_file;

	int call_line;
	const char* call_func;
	const char* call_file;
};

struct Stack
{
	elem_t* data;
	ssize_t size;
	ssize_t capacity;
	struct Stack_info stk_info;
};

unsigned int stack_verificator(const struct Stack* const stk_ptr);

enum error_code stack_init(struct Stack* stk_ptr, const ssize_t start_size);

unsigned int stack_push(struct Stack* const stk_ptr, const elem_t value);

enum error_code stack_dtor(struct Stack* stk_ptr);



#endif /* STACK_H */



