#include <stdio.h>

int main()
{
	void ArrayAdd(int* a1, int* a2, int len, int* result)
	{
		if(len > 0)
		{
			int i = 0;
			for(; i != len; i++)
			{
				result[i] = a1[i] + a2[i];
			}
		}
	}
	int a1[2] = {1 , 3};
	int a2[2] = {2, 1};
	int len = 2;
	int result[2];
	ArrayAdd(a1, a2, len, result);
	
	int test = 400;
	test /= 100;
	printf("%i", test);
	return 0;
}
