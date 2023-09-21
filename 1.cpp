#include <stdio.h>

int main()
{
	int a[] = {1, 2, 3};

	printf("%p\n", &a[0]);

	printf("%p\n", &a);

	printf("%p\n", a);

	int* b = a;

	printf("%p\n", b);  

	printf("%p\n", &b);
}