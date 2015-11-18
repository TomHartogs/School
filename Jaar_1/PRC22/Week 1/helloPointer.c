#include <stdio.h>

int main(void)
{
	int i = 10;
	int* p = &i;    
    	*p += 1;

    	printf("waarde van i: %d\n", i);
    	printf("adres van i : %p\n\n", &i);

    	printf("waarde van p: %p\n", p);
    	printf("adres van p : %p\n", &p);
    	printf("waar p naar wijst: %d\n", *p);

    	return 0;
}

