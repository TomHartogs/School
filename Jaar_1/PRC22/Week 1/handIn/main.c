#include <stdio.h>
#include "parameter.h"

int main()
{
//~ Function 1 
	int a = 1;
	int b = 2;
	printf("int a equals %d\n",  a);
	printf("int b equals %d\n",  b);
	SwapValues(&a, &b);
	printf("Values swapped\n");
	printf("int a now equals %d\n",  a);
	printf("int b now equals %d\n",  b);
	
	int arr[5] = {1, 2, 3, 4, 5};
	int len = 5;
//~	Function 2
	printf("New temp variable the sum is: %d\n", GetSumReturn(arr, len));
	
//~ Function 3
	int sum = 0;
	printf("The sum value is now: %d\n", sum);
	GetSumParameter(arr, len, &sum);
	printf("Sum value changed\n");
	printf("The sum value is now: %d\n", sum);

//~	Function 4
	int arr2[5] = {1, 2, 3, 4, 5};
	int result[5];
	int i = 0;
	for(; i != len; i++)
	{
		printf("%d\n", result[i]);
	}
	ArrayAdd(arr, arr2, len, result);
	i = 0;
	for(; i != len; i++)
	{
		printf("%d\n", result[i]);
	}
	
	return 0;
}
