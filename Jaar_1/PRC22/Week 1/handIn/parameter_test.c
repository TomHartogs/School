#include "parameter.h"
#include "parameter.c"
#include "unity.h" 

void setUp(void)
{
    // This is run before EACH test
}

void tearDown(void)
{
    // This is run after EACH test
}

void SwapValuesTest(void)
{
    int a = 1;
	int b = 2;
	TEST_ASSERT_EQUAL(a, 1);
	TEST_ASSERT_EQUAL(b, 2);
	SwapValues(&a, &b);
	TEST_ASSERT_EQUAL(a, 2);
	TEST_ASSERT_EQUAL(b, 1);
}

void GetSumReturnTest(void)
{
	int number1 = 1;
	int number2 = 4;
    int arr[2];
    arr[0] = number1;
    arr[1] = number2;
	int len = 2;
	TEST_ASSERT_EQUAL(arr[0], 1);
	TEST_ASSERT_EQUAL(arr[1], 4);
	TEST_ASSERT_EQUAL(len, 2);
	TEST_ASSERT_EQUAL((number1 + number2), 5);
	TEST_ASSERT_EQUAL(GetSumReturn(arr, len), 5);
}

int main (int argc, char * argv[])
{
    UnityBegin();
    
    SwapValuesTest();
    
    return UnityEnd();
}
