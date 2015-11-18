#include "parameter.h"

void SwapValues(int* a, int* b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}
int GetSumReturn(int arr[], int len)
{
	int total = 0;
	if(len > 0)
	{
		int i = 0;
		for(; i != len; i++)
		{
			total += arr[i];
		}
	}
	return total;
}
void GetSumParameter(int* arr, int len, int* sum)
{
	if(len > 0)
	{
		int total = 0;
		int i = 0;
		for(; i != len; i++)
		{
			total += arr[i];
		}
		*sum = total;
	}
}
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
