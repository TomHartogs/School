#include <stdio.h>

int array[6] = {1, 2, 3, 4, 5, 6};
int* p = &array[5];

int main(void)
{
	printf("waarde: %p\n", p);
	printf("waarde: %p\n", array);
	for (; p >= array; p--)
	{
		printf("waarde: %d\n", *p);
	}
    return 0;
}
