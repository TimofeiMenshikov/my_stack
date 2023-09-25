#ifndef HASH_H
	#define HASH_H

	#ifdef HASH_PROTECTION

		hash_t calc_hash_stack(struct Stack stk);
		hash_t  calc_hash_data(struct Stack stk);

		#define CALC_HASH_SUM(number)     								\
																		\
		    for (size_t n_byte = 0; n_byte < sizeof(number); n_byte++)	\
		    {															\
				bytes_sum += number % 256; 								\
																		\
				number = number / 256; 									\
			}															\


	#endif /* HASH_PROTECTION */



#endif /* HASH_H */ 