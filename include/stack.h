#ifndef STACK_H
#define STACK_H

typedef int elem_t;
typedef unsigned long long canary_t;
typedef unsigned long long hash_t;




const elem_t POISON_VALUE = 0;

// define работает со стеком
#define get_stack_call_info()          \
	stk.stk_info.call_line = __LINE__; \
	stk.stk_info.call_func = __func__; \
	stk.stk_info.call_file = __FILE__;

// define работает с указателем на стек
#define get_stack_init_info()               \
	stk_ptr->stk_info.init_line = __LINE__; \
	stk_ptr->stk_info.init_func = __func__; \
	stk_ptr->stk_info.init_file = __FILE__;


enum error_code
{
	NO_ERROR = 0,
	STACK_POINTER_IS_NULL = 1,
	STACK_DATA_IS_NULL = 2,
	INVALID_STACK_SIZE = 4,
	INVALID_STACK_CAPACITY = 8,
	STACK_SIZE_LARGER_THAN_CAPACITY = 16,
	UNABLE_TO_INCREASE_STACK = 32,
	UNABLE_TO_DECREASE_STACK = 64

	#ifdef CANARY_PROTECTION
	,
	LEFT_CANARY_DATA_DIED = 128,
	RIGHT_CANARY_DATA_DIED = 256,
	LEFT_CANARY_STACK_DIED = 512,
	RIGHT_CANARY_STACK_DIED = 1024

	#endif /* CANARY_PROTECTION */
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
	#ifdef CANARY_PROTECTION
		canary_t left_canary;
	#endif /* CANARY_PROTECTION */

	elem_t* data;
	ssize_t size;
	ssize_t capacity;

	elem_t last_popped_value; 

	struct Stack_info stk_info;

	#ifdef HASH_PROTECTION 
		hash_t hash_stack;
		hash_t hash_data;
	#endif /* HASH_PROTECTION */

	#ifdef CANARY_PROTECTION
		canary_t right_canary;
	#endif /* CANARY_PROTECTION */
};

unsigned int stack_verificator(const struct Stack* const stk_ptr);

enum error_code stack_init(struct Stack* const stk_ptr, const ssize_t start_size);

unsigned int increase_stack(const size_t increase_coef, struct Stack* const stk_ptr);

unsigned int decrease_stack(const size_t decrease_coef, struct Stack* const stk_ptr);

unsigned int stack_push(struct Stack* const stk_ptr, const elem_t value);

enum error_code stack_dtor(struct Stack* stk_ptr);

unsigned int stack_pop(struct Stack* stk_ptr);

ssize_t get_stack_decrease_lag(const ssize_t capacity);


#endif /* STACK_H */



