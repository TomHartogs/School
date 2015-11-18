#include <stdio.h>
int main(void)
{
	int i;
	int *p1;
	int *p2;
	i = 42;
	printf("waarde i = %d\n", i);
	p1 = &i;
	p2 = &i;
	*p1 = 43;
	printf("waarde i = %d\n", i);
	printf("inhoud p1 = %x\n", (int)p1);
	printf("hello world!\n");
	return 0;
}
