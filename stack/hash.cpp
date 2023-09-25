#include <stdio.h>
#include "../include/stack.h"
#include "../include/hash.h"


#ifdef HASH_PROTECTION
	hash_t calc_hash_stack(struct Stack stk)
	{
		// изменяет данные при расчете хеша => передача не по указателю
		/*
		hash_t bytes_sum = 0;

		CALC_HASH_SUM(stk.capacity);

		size_t data_address_number = (size_t) stk.data; 

		CALC_HASH_SUM(data_address_number);
		CALC_HASH_SUM(stk.size);
		CALC_HASH_SUM(stk.capacity);
		CALC_HASH_SUM(stk.last_popped_value);
		CALC_HASH_SUM(stk.stk_info.call_line);

		size_t call_line_address_number = (size_t) stk.stk_info.call_file;
		size_t call_file_address_number = (size_t) stk.stk_info.call_func;

		CALC_HASH_SUM(call_line_address_number);
		CALC_HASH_SUM(call_file_address_number);

		CALC_HASH_SUM(stk.stk_info.init_line);

		size_t init_line_address_number = (size_t) stk.stk_info.init_file;
		size_t init_file_address_number = (size_t) stk.stk_info.init_func;

		CALC_HASH_SUM(init_line_address_number);
		CALC_HASH_SUM(init_file_address_number);

		#ifdef CANARY_PROTECTION

			CALC_HASH_SUM(stk.left_canary);
			CALC_HASH_SUM(stk.right_canary);

		*/

		//#endif /* CANARY_PROTECTION */

		//return bytes_sum;

		return 0;
	}

	
	#warning do not use such generic name
	hash_t calc_hash_data(struct Stack stk)
	{
		hash_t bytes_sum = 0;

		return bytes_sum;
	}
	/*
		printf("start for\n");

		for (size_t n_elem = 0; n_elem < stk.capacity; n_elem++)
		{
			printf("the number is %d", stk.data[n_elem]);

			CALC_HASH_SUM(stk.data[n_elem]);
			printf("calc %zu\n", n_elem);
		}

		return bytes_sum;
	}*/




#endif /* HASH_PROTECTION */
